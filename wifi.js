(function() {
    const WiFi = require(`windows.devices.wifi`);
    const PasswordCredential = require(`windows.security.credentials`).PasswordCredential;
    const devEnum = require(`windows.devices.enumeration`);
    const Connectivity = require(`windows.networking.connectivity`);
    const deasync = require('deasync');
    const devInfo = devEnum.DeviceInformation;
    const EventEmitter = require('events').EventEmitter;
    const WiFiReconnectionKind = WiFi.WiFiReconnectionKind;
    const WiFiConnectionStatus = WiFi.WiFiConnectionStatus;
    const WiFiAdapter = WiFi.WiFiAdapter;

    var adapter;

    // Rough approximation of percentage quality based on quadratics and assuming a range of -100 dBm to -40 dBm (weak to strong).
    function _rssiToPercent(rssi) {
        if(rssi > -50) {
            return 100;
        }
        rssi += 50;
        return Math.max(Math.min(100 - Math.floor(100 * Math.abs(rssi)/50), 100), 1);
    }


    class wifi extends EventEmitter {
        constructor (adapt) {
            super();

            if (deasync(WiFiAdapter.requestAccessAsync)() !== WiFi.WiFiAccessStatus.allowed) {
                throw new Error('Current user does not have access to wifi adapters.');
            }

            if (adapt) {
                // If an adapter is provided, try to use that.
                if (adapt instanceof devInfo) {
                    if (adapt.isEnabled) {
                        adapter = deasync(WiFiAdapter.fromIdAsync)(adapt.id);
                    } else {
                        throw new Error('Provided adapter is disabled.');
                    }
                } else {
                    throw new Error('Invalid adapter provided. Use wifi.listAdapters() to retrieve a list of valid adapters.');
                }
            } else {
                // Otherwise, find the best adapter available.
                // Looks for a default and if there is none takes the first enabled adapter.
                let adapters = listAdapters();
                
                var best;
                for(adapt in adapters) {
                    adapt = adapters[adapt];
    
                    if (adapt.isEnabled) {
                        let wifiadapt = deasync(WiFiAdapter.fromIdAsync)(adapt.id);
                        if (adapt.isDefault) {
                            adapter = wifiadapt;
                        } else if (!best) {
                            best = wifiadapt;
                        }
                    }
                }
    
                if (!best) {
                    throw new Error('No enabled wifi adapters!');
                } else {
                    adapter = best;
                }
            }

            adapter.on('availableNetworksChanged', () => {
                this.emit('availableNetworksChanged', availableNetworks());
            });
        }
    }

    wifi.listAdapters = listAdapters = function() {
        let queryString = WiFiAdapter.getDeviceSelector();
        let adapters = deasync(devEnum.DeviceInformation.findAllAsync)(queryString);
        
        adapters = adapters.first();
        
        let list = [];

        var best;
        while(adapters.hasCurrent) {
            let adapt = adapters.current;
            adapters.moveNext();
            
            list.push(adapt);
        }

        return list;
    }

    //  CONNECTION STATUSES-------------------
    //  unspecifiedFailure: 0,
    //  success: 1,
    //  accessRevoked: 2,
    //  invalidCredential: 3,
    //  networkNotAvailable: 4,
    //  timeout: 5,
    //  unsupportedAuthenticationProtocol: 6
    //  --------------------------------------

    wifi.connectionStatus = WiFiConnectionStatus;

    /**
     * Usage: connect(ssid, [opts])
     * auto defaults to true, but will not change a known network. To change a known network, use remember instead.
     * if security is defined, there is no guarantee that the resulting profile will be accurate
     * otherwise, it will scan for the given ssid and attempt to extract security information
     * valid options: auto, password
     */

    wifi.prototype.connect = connect = function (ssid, opts) {
        if (!opts) {
            opts = {};
        }

        let self = this;

        let auto = opts.auto || true;
        let password = opts.password;

        return new Promise((resolve, reject) => {
            let networks = adapter.networkReport.availableNetworks.first();
            let network;
            while(networks.hasCurrent) {
                let net = networks.current;
                networks.moveNext();

                if (net.ssid === ssid) {
                    // Find the strongest BSSID associated with the given SSID.
                    if (!network || net.networkRssiInDecibelMilliwatts > network.networkRssiInDecibelMilliwatts) {
                        network = net;
                    }
                }
            }
            if (network) {
                let reconnectKind = auto ? WiFiReconnectionKind.automatic : WiFiReconnectionKind.manual;
                if (password) {
                    let passcred = new PasswordCredential();
                    if (password && typeof password === 'string' && password.length > 0) {
                        passcred.password = password;
                    }
                    adapter.connectAsync(network, reconnectKind, passcred, handleConnectionStatus);
                } else {
                    adapter.connectAsync(network, reconnectKind, handleConnectionStatus);
                }

                function handleConnectionStatus(err, result) {
                    let status = result.connectionStatus;
                    if (err) {
                        reject(err);
                    } else {
                        if (status === WiFiConnectionStatus.success) {
                            self.emit('networkConnected', ssid);
                        }
                        resolve(status);
                    }
                }
            } else {
                reject(new Error('No networks available with the given SSID.'));
            }
        });
    }

    // Usage: wifi.disconnect()
    wifi.prototype.disconnect = disconnect = function() {
        adapter.disconnect();
    }


    // Usage: availableNetworks([ssid])
    // ssid is anticipated as a regular expression.  Will not match exactly unless the regex specifies such.
    wifi.prototype.availableNetworks = availableNetworks = function(ssid) {
        let connections = currentConnections();

        let networks = adapter.networkReport.availableNetworks.first();
        let results = {};
        while(networks.hasCurrent) {
            let net = networks.current;
            networks.moveNext();

            let network = {};
            network.ssid = net.ssid;
            network.signal = _rssiToPercent(net.networkRssiInDecibelMilliwatts)/100;
            network.connected = connections.indexOf(net.ssid) >= 0;
            network.security = _rewriteSecurity(net.securitySettings);

            // Check if the ssid matches the given regex.
            if ((!ssid || net.ssid.match(ssid)) &&
                (!results[net.ssid] || network.signal > results[net.ssid].signal)) {
                // If this is a new SSID, add it to the results.
                // If this isn't new but is stronger, overwrtie the last result.
                results[net.ssid] = network;
            }
        }

        return results;
    }


    // Usage: scan()
    wifi.prototype.scan = scan = function() {
        adapter.scanAsync(() => {});
    }

    /* Auth Types
        "none": 0,
        "unknown": 1,
        "open80211": 2,
        "sharedKey80211": 3,
        "wpa": 4,
        "wpaPsk": 5,
        "wpaNone": 6,
        "rsna": 7,
        "rsnaPsk": 8,
        "ihv": 9
    */
    function _rewriteSecurity(security) {
        if (!security instanceof Connectivity.NetworkSecuritySettings) {
            throw new Error("Invalid NetworkSecuritySettings object provided.");
        }
        const eTypes = Connectivity.NetworkEncryptionType;
        const aTypes = Connectivity.NetworkAuthenticationType;

        let authType = security.networkAuthenticationType;
        let encryptType = security.networkEncryptionType;
        
        switch(authType) {
            // Secure types
            case aTypes.wpa:
                return 'WPA-Enterprise';
            case aTypes.wpaPsk:
                return 'WPA-Personal';
            case aTypes.wpaNone:
                return 'WPA-None';
            case aTypes.rsna:
                return 'WPA2-Enterprise';
            case aTypes.rsnaPsk:
                return 'WPA2-Personal';
            
            // Not recommended
            case aTypes.sharedKey80211:
                return 'WEP Shared';
            
            // Unknown types            
            case aTypes.unknown:
                return 'Unknown'
            case aTypes.ihv:
                return 'IHV';
        
            // Unsecure types
            case aTypes.open80211:
                return 'Open'
            case aTypes.none:
                return 'None';
            
            default:
                throw new Error(`Invalid auth type "${authType}"`);
        }
    }

    // Usage: currentConnections()
    wifi.currentConnections = currentConnections = function() {
        let filter = new Connectivity.ConnectionProfileFilter();
        filter.isConnected = true;
        filter.isWlanConnectionProfile = true;

        let netInfo = deasync(Connectivity.NetworkInformation.findConnectionProfilesAsync)(filter);

        let connections = [];

        netInfo = netInfo.first();
        while(netInfo.hasCurrent) {
            let conn = netInfo.current;
            netInfo.moveNext();
            
            connections.push(conn.wlanConnectionProfileDetails.getConnectedSsid());
        }
        return connections;
    }

    // Incomplete
    // knownNetworks = function() {
    //     let filter = new Connectivity.ConnectionProfileFilter();
    //     filter.isWlanConnectionProfile = true;
    //     let profiles = deasync(Connectivity.NetworkInformation.findConnectionProfilesAsync)(filter);
        
    //     let known = [];

    //     profiles = profiles.first();
    //     while(profiles.hasCurrent) {
    //         let conn = profiles.current;
    //         profiles.moveNext();
            
    //         known.push(conn.profileName);
    //     }
    //     return known;
    // }

    module.exports = wifi;
})();

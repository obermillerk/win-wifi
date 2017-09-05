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
                if (password || username) {
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

    // Usage: scan([ssid])
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

    wifi.prototype.scan = scan = function() {
        adapter.scanAsync(() => {});
    }

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
            case aTypes.Wpa:
                return 'WPA-Enterprise';
            case aTypes.WpaPsk:
                return 'WPA-Personal';
            case aTypes.WpaNone:
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

    /*  Old/Unimplemented

        // Usage: isNetworkKnown([ssid, [opts]])
        // valid options: iface
        function isNetworkKnown(ssid, opts) {
            if (ssid === undefined || ssid === null) {
                return false;
            }
            var cmd = `netsh wlan show profiles`;

            if (!opts) {
                opts = {};
            }

            let iface = opts.iface;

            if (iface) {
                cmd += ` interface="${iface}"`;
            }
            try {
                out = execSync(cmd).toString();
                return filterProfiles(out);
            } catch(err) {
                // ignore for now because of incorrect errors from node
                return false;
            }

            function filterProfiles(out) {
                var profiles = out.split('User profiles\r\n')[1].split('\r\n');
                    profiles.splice(0, 1);
                    profiles.splice(-2, 2);

                if (profiles !== '    <None>') {
                    for (let profile in profiles) {
                        profile = profiles[profile].split(': ')[1];
                        if (profile == ssid) {
                            return true;
                        }
                    }
                }
                return false;
            }
        }

        // Usage: forgetNetwork([[ssid,] opts])
        // valid options: iface
        function forgetNetwork(ssid, opts) {
            return new Promise((resolve, reject) => {
                var cmd = `netsh wlan delete profile name="${ssid}"`

                if (ssid && typeof ssid === 'object') {
                    opts = ssid;
                    ssid = undefined;
                }

                if (!opts) {
                    opts = {};
                }

                let iface = opts.iface;

                if (iface) {
                    cmd += ` interface="${iface}"`
                }

                try {
                    execSync(cmd);
                    resolve();
                } catch(err) {
                    reject(err);
                }
            });
        }

        // Usage: rememberNetwork(ssid, opts)
        // password field required for WPAPSK and WPA2PSK security options
        // auto-connect mode only available for password secured networks to avoid unwanted connection to unsecured networks.
        // valid options: auto, password, security, iface
        function rememberNetwork(ssid, opts) {
            let tmpDir = `${__dirname}/tmp`
            return (new Promise((resolve, reject) => {

                if (!opts) {
                    opts = {};
                }

                let auto        = opts.auto || true;
                let password    = opts.password;
                let security    = opts.security;
                let iface       = opts.iface;

                var hexssid = Buffer.from(ssid).toString('hex');
                let mode = auto ? 'auto' : 'manual';

                var profileContent;
                switch(security) {
                    case 'WPA2PSK':
                    case 'WPAPSK':
                    // case 'Open':
                        let template = Handlebars.compile(fs.readFileSync(`${__dirname}/wlan-profile-templates/${security}.xml`,'utf8'));
                        profileContent = template({ssid: ssid, hexssid: hexssid, security: security, password: password, mode: mode})
                        break;
                    default:
                        throw new Error(`Invalid or unsupported authorization type: "${security}"`);
                }

                if (!fs.existsSync(tmpDir)) {
                    fs.mkdirSync(tmpDir);
                }
                let filepath = `${tmpDir}/${ssid}.xml`;
                if (fs.existsSync(filepath)) {
                    fs.unlinkSync(filepath);
                }
                fs.writeFileSync(filepath, profileContent);

                var cmd = `netsh wlan add profile filename="${filepath}"`;

                if (iface) {
                    cmd += ` interface="${iface}"`;
                }

                try {
                    execSync(cmd);
                } catch(err) {
                    reject(err);
                } finally {
                    fs.unlinkSync(filepath);
                    fs.rmdirSync(tmpDir);
                }
            }).catch((err) => {
                // Clean up if something goes wrong.
                // Don't want a file with the password sitting around.
                let filepath = `${tmpDir}/${ssid}.xml`;
                if (fs.existsSync(filepath)) {
                    fs.unlinkSync(filepath);
                }
                if (fs.existsSync(tmpDir)) {
                    fs.rmdirSync(tmpDir);
                }
                // Propogate error
                return Promise.reject(err);
            }));
        }

        function setPreferred(ssid, iface) {
            var cmd = `netsh wlan set profileorder`
        }
    */

    module.exports = wifi;
})();

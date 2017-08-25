(function() {
    const WiFi = require('windows.devices.wifi');
    const PasswordCredential = require('windows.security.credentials').PasswordCredential;
    const devEnum = require('windows.devices.enumeration');
    const deasync = require('deasync');
    const devInfo = devEnum.DeviceInformation;
    const WiFiReconnectionKind = WiFi.WiFiReconnectionKind;
    const WiFiConnectionStatus = WiFi.WiFiConnectionStatus;
    const WiFiAdapter = WiFi.WiFiAdapter;

    var adapter;

    // Rough approximation of percentage quality based on quadratics and assuming a range of -100 dBm to -40 dBm (weak to strong).
    function _rssiToPercent(rssi) {
        if(rssi > -40) {
            return 100;
        }
        rssi += 40;
        return Math.max(Math.min(100 - Math.floor(rssi*rssi / 36), 100), 1);
    }


    function wifi(adapt) {
        // If an adapter is provided, try to use that.
        if (adapt) {
            if (adapt instanceof devInfo) {
                if (adapt.isEnabled) {
                    adapter = deasync(WiFiAdapter.fromIdAsync)(adapt.id);
                } else {
                    throw new Error('Provided adapter is disabled.');
                }
                return;
            } else {
                throw new Error('Invalid adapter provided. Use wifi.listAdapters() to retrieve a list of valid adapters.');
            }
        }

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

    function afterConnect(err, results) {
        if(err) {
            console.error(err);
        }
        console.log(results.connectionStatus);
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
     * valid options: auto, password, security, iface
     */

    wifi.connect = connect = function (ssid, opts) {
        if (!opts) {
            opts = {};
        }

        let auto = opts.auto || true;
        let password = opts.password;
        let username = opts.username;

        return new Promise((resolve, reject) => {
            if (!adapter) {
                reject(new Error('Not initialized. Use wifi() or wifi(adapter) to initialize.'));
            }
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
                    if (username && typeof username === 'string' && username.lenght > 0) {
                        passcred.userName = username;
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
                        resolve(status);
                    }
                }
            } else {
                reject(new Error('No networks available with the given SSID.'));
            }
        });
    }

    // Usage: wifi.disconnect()
    wifi.disconnect = disconnect = function() {
        if (!adapter) {
            throw new Error('Not initialized. Use wifi() or wifi(adapter) to initialize.')
        }

        adapter.disconnect();
    }

    // Usage: scan([[ssid,] opts])
    // valid options: iface
    function scan(ssid, opts) {
        var results = {};
        var cmd = `netsh wlan show networks mode=bssid`

        if (ssid && typeof ssid === 'object') {
            opts = ssid;
            ssid = undefined;
        }

        if (!opts) {
            opts = {};
        }

        let iface = opts.iface;

        if(iface) {
            cmd += ` interface="${iface}"`
        }

        let connected = currentConnections(iface);
        for (let i in connected) {
            connected[i] = connected[i].state;
        }

        let out = execSync(cmd).toString();

        out = out.replace(/  +/g, ' ').replace(/(\r\n) | (: )/g, '$1$2');
        let interfaces = out.split('Interface name : ');
        interfaces.forEach((iface) => {
            let networks = iface.split('\r\n\r\n');
            if (res = networks[0].match(/Interface name: (.*) \r\n/)) {
                iface = res[1];
                networks.splice(0,1);
                networks.splice(-1, 1)

                networks.forEach((network) => {
                    network = network
                        .replace(/\bSSID \d+:/g, 'SSID:');
                    network = parseNetworkInfo(network.split('\r\n'));
                    if (network !== null) {
                        results[network.ssid] = network;
                    }
                });

                function parseNetworkInfo(lines) {
                    let network = {iface: iface};
                    lines.forEach((line) => {
                        let res;
                        if (res = line.match(/SSID: (.*)/)) {
                            network.ssid = res[1];
                        } else if (res = line.match(/Authentication: (.*)/)) {
                            network.security = _rewriteSecurity(res[1]);
                        } else if (res = line.match(/Signal: (\d*)%/)) {
                            network.signal = res[1]/100;
                        }
                    });

                    network.state = connected[network.ssid] || 'disconnected';
                    network.known = isNetworkKnown(network.ssid);

                    if (network && network.iface && network.ssid && network.security) {
                        return network;
                    } else {
                        return null;
                    }
                }
            }
        });

        return results;
    }

    function _rewriteSecurity(security) {
        switch(security) {
            case 'WPA2-Personal':
                return 'WPA2PSK';
            case 'WPA-Personal':
                return 'WPAPSK';
            default:
                return security;
        }
    }

    // Usage: currentConnections([opts])
    // valid options: iface
    function currentConnections(opts) {
        var cmd = `netsh wlan show interfaces`

        if (!opts) {
            opts = {};
        }

        let iface = opts.iface;

        if (iface) {
            cmd += ` interface="${iface}"`;
        }

        let out = execSync(cmd).toString();

        out = out.replace(/  +/g, ' ').replace(/(\r\n) | (: )/g, '$1$2');

        let ifaces = out.split('\r\n\r\n');
        let connections = {};

        ifaces.forEach((iface) => {
            let connection = {};
            var ifaceExp = /^Name: ([^\r\n]*)\r\n/;
            var ssidExp  = /\r\nSSID: ([^\r\n]*)\r\n/;
            var secExp   = /\r\nAuthentication: ([^\r\n]*)\r\n/;
            var stateExp = /\r\nState: ([^\r\n]*)\r\n/;
            var sigExp   = /\r\nSignal: (\d*)% \r\n/;
            let res;
            if (res = iface.match(ifaceExp)) {
                connection.iface    = res[1];
            }
            if (res = iface.match(ssidExp)) {
                connection.ssid     = res[1];
            }
            if (res = iface.match(secExp)) {
                connection.security = _rewriteSecurity(res[1]);
            }
            if (res = iface.match(sigExp)) {
                connection.signal = res[1]/100
            }
            if (res = iface.match(stateExp)) {
                connection.state = res[1];

                if (connection.state === 'authenticating') {
                    connection.state = 'connecting';
                }
            }

            if (connection.state && (connection.state === 'connected' || connection.state ==='connecting')) {
                connections[connection.ssid] = connection;
            }
        });
        return connections;
    }

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

    module.exports = wifi;
})();

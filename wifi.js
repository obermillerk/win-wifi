(function() {
    const exec = require('child_process').exec;
    const execSync = require('child_process').execSync;
    const fs = require('fs');
    const Handlebars = require('handlebars');

    /**
     * Usage: connect(ssid, [opts])
     * auto defaults to true, but will not change a known network. To change a known network, use remember instead.
     * if security is defined, there is no guarantee that the resulting profile will be accurate
     * otherwise, it will scan for the given ssid and attempt to extract security information
     * valid options: auto, password, security, iface
     */
    function connect(ssid, opts) {
        return new Promise((resolve, reject) => {
            var cmd = `netsh wlan connect ssid="${ssid}" name="${ssid}"`;

            if (!ssid) {
                reject(new Error('No SSID provided'));
            }

            let auto        = opts.auto || true;
            let password    = opts.password;
            let security    = opts.security;
            let iface       = opts.iface;

            if (iface) {
                if(typeof iface === 'string') {
                    cmd += `interface="${iface}"`;
                } else {
                    reject(new Error('Invalid interface'));
                }
            }

            if (isNetworkKnown(ssid, iface)) { // If known, connect
                exec(cmd);
            } else { // If not known, remember
                if (!security) {
                    let network = scan(iface)[ssid];
                    if (network) {
                        resolve(rememberNetwork(ssid, network.security, password, auto, iface));
                    } else {
                        reject(new Error('Network not found.'))
                    }
                } else {
                    resolve(rememberNetwork(ssid, security, password, auto, iface));
                }
            }
        });
    }

    // Usage: disconnect([[ssid,] opts])
    // valid options: iface
    function disconnect(ssid, opts) {
        return new Promise((resolve, reject) => {
            var cmd = `netsh wlan disconnect`;

            if (ssid && typeof ssid === 'object') {
                opts = ssid;
                ssid = undefined;
            }

            let iface = opts.iface;

            if (iface) {
                cmd += ` interface="${iface}"`;
            }

            try {
                let out = execSync(cmd);
                resolve(out)
            } catch(err) {
                reject(err);
            }
        });
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

                    network.known = isNetworkKnown(network.ssid);
                    network.state = connected[network.ssid] || 'disconnected';
                    
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

    // Usage: currentConnections([[ssid,] opts])
    // valid options: iface
    function currentConnections(ssid, opts) {
        var cmd = `netsh wlan show interfaces`

        if (ssid && typeof ssid === 'object') {
            opts = ssid;
            ssid = undefined;
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

    // Usage: isNetworkKnown([[ssid,] opts])
    // valid options: iface
    function isNetworkKnown(ssid, opts) {
        if (ssid === undefined || ssid === null) {
            return false;
        }
        var cmd = `netsh wlan show profiles`;

        if (ssid && typeof ssid === 'object') {
            opts = ssid;
            ssid = undefined;
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

    module.exports = {
        connect: connect,
        disconnect: disconnect,
        scan: scan,
        rememberNetwork: rememberNetwork,
        forgetNetwork: forgetNetwork,
        isNetworkKnown: isNetworkKnown,
        currentConnections: currentConnections
    }
})();

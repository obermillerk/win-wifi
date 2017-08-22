(function() {
    const exec = require('child_process').exec;
    const execSync = require('child_process').execSync;
    const fs = require('fs');
    const Handlebars = require('handlebars');

    // Usage: connect(ssid, [auto, [password, [security, [iface]]]]);
    // auto field is required to define password,
    // password field is required to define security,
    // security field is required to define iface
    // for any, to pass an unknown/unneeded, null should be passed
    // auto defaults to true, but will not change a known network
    // if security is defined, there is no guarantee that the resulting profile will be accurate
    // otherwise, it will scan for the given ssid and attempt to extract security information
    function connect(ssid, auto, password, security, iface) {
        return new Promise((resolve, reject) => {
            var cmd = `netsh wlan connect ssid="${ssid}" name="${ssid}"`;

            if (!ssid) {
                reject(new Error('No SSID provided'));
            }

            if (auto === null || auto === undefined) {
                auto = true;
            }

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
                    scan(iface).then((results) => {
                        let network = results[ssid];
                        if (network) {
                            resolve(rememberNetwork(ssid, network.security, password, auto, iface));
                        } else {
                            reject(new Error('Network not found.'))
                        }
                    });
                } else {
                    resolve(rememberNetwork(ssid, security, password, auto, iface));
                }
            }
        });
    }

    function disconnect(iface) {
        return new Promise((resolve, reject) => {
            var cmd = `netsh wlan disconnect`;

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

    function scan(iface) {
        var results = {};
        var cmd = `netsh wlan show networks mode=bssid`

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
            iface = networks[0].match(/Interface name: (.*) \r\n/)[1];
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

    function currentConnections(iface) {
        var cmd = `netsh wlan show interfaces`

        if (iface) {
            cmd += ` interface="${iface}"`;
        }

        let out = execSync(cmd).toString();

        let ifaces = out.split('\r\n\r\n');
        let connections = {};

        ifaces.forEach((iface) => {
            let connection = {};
            var ifaceExp = /^    Name                   : ([^\r\n]*)\r\n/;
            var ssidExp  = /\r\n    SSID                   : ([^\r\n]*)\r\n/;
            var secExp   = /\r\n    Authentication         : ([^\r\n]*)\r\n/;
            var stateExp = /\r\n    State                  : ([^\r\n]*)\r\n/;
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

    function isNetworkKnown(ssid, iface) {
        if (ssid === undefined || ssid === null) {
            return false;
        }
        var cmd = `netsh wlan show profiles`;
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

    function forgetNetwork(ssid, iface) {
        return new Promise((resolve, reject) => {
            var cmd = `netsh wlan delete profile name="${ssid}"`

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

    // Usage: rememberNetwork(ssid, security, [password, [auto]], [iface])
    // password field required for WPAPSK and WPA2PSK security options
    // auto-connect mode only available for password secured networks to avoid unwanted connection to unsecured networks.
    function rememberNetwork(ssid, security, password, auto, iface) {
        let tmpDir = `${__dirname}/tmp`
        return (new Promise((resolve, reject) => {
            var hexssid = Buffer.from(ssid).toString('hex');
            let mode = auto ? 'auto' : 'manual';

            var profileContent;
            switch(security) {
                case 'WPA2PSK':
                case 'WPAPSK':
                case 'open':
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

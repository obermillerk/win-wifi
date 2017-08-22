(function() {
    const exec = require('child_process').exec;
    const execSync = require('child_process').execSync;
    const fs = require('fs');
    const Handlebars = require('handlebars');

    // Usage: connect(ssid, [password, [security, [iface]]]);
    // password field is required to define security,
    // security field is required to define iface
    // for either, to pass an unknown/unneeded, null should be passed
    // if security is defined, there is no guarantee that the resulting profile will be accurate
    // otherwise, it will scan for the given ssid and attempt to extract security information
    function connect(ssid, password, security, iface) {
        return new Promise((resolve, reject) => {
            var cmd = `netsh wlan connect ssid="${ssid}" name="${ssid}"`;

            if (iface) {
                if(typeof iface === 'string') {
                    cmd += `interface="${iface}"`;
                } else {
                    reject(new Error('Invalid interface'));
                }
            }

            //return isNetworkKnown(ssid, iface).then((known) => {
                //if (known) { // If known, connect
                if (false) {
                    exec(cmd);
                } else { // If not known, remember
                    if (!security) {
                        scan(iface).then((results) => {
                            let network = results[ssid];
                            if (network) {
                                // TODO: ask user for auto-connect mode
                                resolve(rememberNetwork(ssid, network.security, password, true, iface));
                            } else {
                                reject(new Error('Network not found.'))
                            }
                        });
                    } else {
                        resolve(rememberNetwork(ssid, security, password, true, iface));
                    }
                }
            // });
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
        return new Promise((resolve, reject) => {
            var results = {};
            var cmd = `netsh wlan show networks mode=bssid`

            if(iface) {
                cmd += ` interface="${iface}"`
            }

            try {
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
                            .replace(/\bSSID \d+:/g, 'SSID:')
                            .replace(/\nAuthentication: WPA2-Personal/g,'\nAuthentication: WPA2PSK')
                            .replace(/\nAuthentication: WPA-PERSONAL/g, '\nAuthentication: WPAPSK');
                        network = parseNetworkInfo(network.split('\r\n'));
                        if (network !== null) {
                            results[network.ssid] = network;
                        }
                    });

                    function parseNetworkInfo(lines) {
                        // For now, just interface, ssid, and security.
                        let network = {iface: iface};
                        lines.forEach((line) => {
                            let res;
                            if (res = line.match(/SSID: (.*)/)) {
                                network.ssid = res[1];
                            } else if (res = line.match(/Authentication: (.*)/)) {
                                network.security = res[1];
                            }
                        });

                        if (network && network.iface && network.ssid && network.security) {
                            return network;
                        } else {
                            return null;
                        }
                    }
                });
                resolve(results);
            } catch(err) {
                reject(err);
            }
        });
    }

    function currentConnections(iface) {
        var cmd = `netsh wlan show interfaces`
    }

    function isNetworkKnown(ssid, iface) {
        return new Promise((resolve, reject) => {
            var cmd = `netsh wlan show profiles`;
            if (iface) {
                cmd += ` interface="${iface}"`;
            }
            try {
                out = execSync(cmd)//,(err, out, stderr) => {
                //     console.error(err);
                //     if (err || out === 'There is no such wireless interface on the system.\r\n') {
                //         reject(err);
                //     } else {
                //         filterProfiles(out)
                //     }
                // })
                .toString();
                filterProfiles(out);
            } catch(err) {
                console.log('error!', err);
                reject(err);
            }

            function filterProfiles(out) {
                var profiles = out.split('User profiles\r\n')[1].split('\r\n');
                    profiles.splice(0, 1);
                    profiles.splice(-2, 2);
                
                if (profiles !== '    <None>') {
                    for (let profile in profiles) {
                        profile = profiles[profile].split(': ')[1];
                        if (profile == ssid) {
                            resolve(true);
                        }
                    }
                }
                resolve(false);
            }
        })
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

            if (!fs.existsSync('tmp')) {
                fs.mkdirSync('tmp');
            }
            let filepath = `./tmp/${ssid}.xml`;
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
                fs.rmdirSync('tmp');
            }
        }).catch((err) => {
            // Clean up if something goes wrong.
            // Don't want a file with the password sitting around.
            let filepath = `./tmp/${ssid}.xml`;
            if (fs.existsSync(filepath)) {
                fs.unlinkSync(filepath);
            }
            if (fs.existsSync('tmp')) {
                fs.rmdirSync('tmp');
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
        // isNetworkKnown: isNetworkKnown
    }
})();

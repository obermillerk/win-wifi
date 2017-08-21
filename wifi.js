(function() {
    const exec = require('child_process').exec;
    const fs = require('fs');
    const Handlebars = require('handlebars');

    // Usage: connect(ssid, [password, [iface]]);
    // password field is required to define iface
    function connect(ssid, password, iface) {
        var cmd = `netsh wlan connect ssid="${ssid}" name="${ssid}"`

        if (iface) {
            if(typeof iface === 'string') {
                cmd += `interface="${iface}"`
            } else {
                throw new Error('Invalid interface');
            }
        }

        return new Promise((resolve, reject) => {
            isNetworkKnown(ssid, iface).then((res) => {
                if (res) {
                    exec(cmd);
                } else {
                    
                    // TODO: retrieve security, maybe ask user for auto-connect mode
                    rememberNetwork(ssid, password, true, iface);
                }
            });
        });
    }

    function disconnect(iface) {
        var cmd = `netsh wlan disconnect`;

        if (iface) {
            cmd += ` interface="${iface}"`;
        }

        exec(cmd, (err, resp) => {
            if (err) {
                console.error(err);
            }
            console.log(resp);
        });
    }

    function scan(iface) {
        return new Promise((resolve, reject) => {
            var results = {};
            var cmd = `netsh wlan show networks mode=bssid`

            if(iface) {
                cmd += ` interface="${iface}"`
            }
            exec(cmd, (err, stdout) => {
                stdout = stdout.replace(/  +/g, ' ').replace(/(\r\n) | (: )/g, '$1$2');
                let interfaces = stdout.split('Interface name : ');
                interfaces.forEach((iface) => {
                    let networks = iface.split('\r\n\r\n');
                    iface = networks[0];
                    networks.splice(0,1);

                    networks.forEach((network) => {
                        let lines = network.split('\r\n');
                        console.log(network);
                    })
                })
                if (err) {
                    reject(err);
                }
                resolve();
            });
        })
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
            exec(cmd,(err, out) => {
                if (err || out === 'There is no such wireless interface on the system.\r\n') {
                    reject(err);
                } else {
                    filterProfiles(out)
                }
            });

            function filterProfiles(out) {
                var profiles = out.split('User profiles\r\n')[1].split('\r\n');
                    profiles.splice(0, 1);
                    profiles.splice(-2, 2);

                for (let profile in profiles) {
                    profile = profiles[profile].split(': ')[1];
                    if (profile == ssid) {
                        resolve(true);
                    }
                }
                resolve(false);
            }
        })
    }

    function forgetNetwork(ssid, iface) {
        var cmd = `netsh wlan delete profile name="${ssid}"`

        if (iface) {
            cmd += ` interface="${iface}"`
        }

        exec(cmd, (err, resp) => {
            if(err) {
                consoel.error(err);
            }
        });
    }

    // Usage: rememberNetwork(ssid, security, [password, [auto]], [iface])
    // password field required for WPAPSK and WPA2PSK security options
    // auto-connect mode only available for password secured networks to avoid unwanted connection to unsecured networks.
    function rememberNetwork(ssid, security, password, auto, iface) {
        return new Promise(() => {
            var hexssid = Buffer.from(ssid).toString('hex');
            let mode = auto ? 'auto' : 'manual';

            var profileContent;
            switch(security) {
                case 'WPA2PSK':
                case 'WPAPSK':
                case 'open':
                    let template = Handlebars.compile(fs.readFileSync(`./app/common/io/wlan-profile-templates/${security}.xml`,'utf8'));
                    profileContent = template({ssid: ssid, hexssid: hexssid, security: security, password: password, mode: mode})
                    break;
                default:
                    throw new Error(`Invalid or unsupported authorization type: "${security}"`);
            }

            let filepath = `${ssid}.xml`
            fs.writeFileSync(filepath, profileContent);

            var cmd = `netsh wlan add profile filename="${ssid}.xml"`;

            if (iface) {
                cmd += ` interface="${iface}"`;
            }

            exec(cmd, (err, resp) => {
                if(err) {
                    console.error(err);
                }
                fs.unlinkSync(filepath);
            });
        });
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
        isNetworkKnown: isNetworkKnown
    }
})();

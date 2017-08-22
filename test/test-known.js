require('dotenv').config();
let wifi = require('../wifi');

var ssid     = process.env.SSID,
    password = process.env.PASS,
    security = process.env.AUTH,
    auto     = process.env.AUTO,
    iface    = process.env.IFACE

let opts = {
    password: password,
    security: security,
    auto: auto,
    iface: iface
}

if (wifi.isNetworkKnown(ssid, opts)) {
    console.log(`network "${ssid}" is known`);
} else {
    console.log(`network "${ssid}" is unknown`);
}

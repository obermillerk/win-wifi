require('dotenv').config();
let wifi = require('../wifi');

var ssid     = process.env.SSID,
    password = process.env.PASS,
    security = process.env.AUTH,
    auto     = process.env.AUTO,
    iface    = process.env.IFACE

if (wifi.isNetworkKnown(ssid, iface)) {
    console.log(`network "${ssid}" is known`);
} else {
    console.log(`network "${ssid}" is unknown`);
}

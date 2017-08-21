require('dotenv').config();
let wifi = require('../wifi');

var ssid     = process.env.SSID,
    password = process.env.PASS,
    security = process.env.AUTH,
    auto     = process.env.AUTO,
    iface    = process.env.IFACE

wifi.isNetworkKnown(ssid, iface)
    .then((res) => {
        if (res) {
            console.log(`network "${ssid}" is known`);
        } else {
            return Promise.reject();
        }
    })
    .catch(() => {
        console.log(`network "${ssid}" is unknown`);
    });

require('dotenv').config();
let wifi = require('../wifi');

var ssid     = process.env.SSID,
    password = process.env.PASS,
    security = process.env.AUTH,
    auto     = process.env.AUTO,
    iface    = process.env.IFACE

console.log(wifi.currentConnections(iface));

require('dotenv').config();
let wifi = new (require('../wifi'))();

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

wifi.disconnect(opts);

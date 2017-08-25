_WiFiNetworkKind = function () {
  this.any = 0;
  this.infrastructure = 1;
  this.adhoc = 2;
}
exports.WiFiNetworkKind = new _WiFiNetworkKind();

_WiFiPhyKind = function () {
  this.unknown = 0;
  this.fhss = 1;
  this.dsss = 2;
  this.iRBaseband = 3;
  this.ofdm = 4;
  this.hrdsss = 5;
  this.erp = 6;
  this.hT = 7;
  this.vht = 8;
  this.dmg = 9;
}
exports.WiFiPhyKind = new _WiFiPhyKind();

_WiFiAccessStatus = function () {
  this.unspecified = 0;
  this.allowed = 1;
  this.deniedByUser = 2;
  this.deniedBySystem = 3;
}
exports.WiFiAccessStatus = new _WiFiAccessStatus();

_WiFiReconnectionKind = function () {
  this.automatic = 0;
  this.manual = 1;
}
exports.WiFiReconnectionKind = new _WiFiReconnectionKind();

_WiFiConnectionStatus = function () {
  this.unspecifiedFailure = 0;
  this.success = 1;
  this.accessRevoked = 2;
  this.invalidCredential = 3;
  this.networkNotAvailable = 4;
  this.timeout = 5;
  this.unsupportedAuthenticationProtocol = 6;
}
exports.WiFiConnectionStatus = new _WiFiConnectionStatus();

WiFiAdapter = (function () {
  var cls = function WiFiAdapter() {
    this.networkAdapter = new Object();
    this.networkReport = new WiFiNetworkReport();
  };
  

  cls.prototype.scanAsync = function scanAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.connectAsync = function connectAsync(availableNetwork, reconnectionKind, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="availableNetwork" type="WiFiAvailableNetwork">A param.</param>
    /// <param name="reconnectionKind" type="WiFiReconnectionKind">A param.</param>
    /// </signature>
  }

cls.prototype.connectAsync = function connectAsync(availableNetwork, reconnectionKind, passwordCredential, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="availableNetwork" type="WiFiAvailableNetwork">A param.</param>
    /// <param name="reconnectionKind" type="WiFiReconnectionKind">A param.</param>
    /// <param name="passwordCredential" type="Object">A param.</param>
    /// </signature>
  }

cls.prototype.connectAsync = function connectAsync(availableNetwork, reconnectionKind, passwordCredential, ssid, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="availableNetwork" type="WiFiAvailableNetwork">A param.</param>
    /// <param name="reconnectionKind" type="WiFiReconnectionKind">A param.</param>
    /// <param name="passwordCredential" type="Object">A param.</param>
    /// <param name="ssid" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.disconnect = function disconnect() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.findAllAdaptersAsync = function findAllAdaptersAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }



  cls.fromIdAsync = function fromIdAsync(deviceId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceId" type="String">A param.</param>
    /// </signature>
  }



  cls.requestAccessAsync = function requestAccessAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }



  cls.getDeviceSelector = function getDeviceSelector() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.WiFiAdapter = WiFiAdapter;

WiFiNetworkReport = (function () {
  var cls = function WiFiNetworkReport() {
    this.availableNetworks = new Object();
    this.timestamp = new Date();
  };
  

  return cls;
}) ();
exports.WiFiNetworkReport = WiFiNetworkReport;

WiFiAvailableNetwork = (function () {
  var cls = function WiFiAvailableNetwork() {
    this.beaconInterval = new Number();
    this.bssid = new String();
    this.channelCenterFrequencyInKilohertz = new Number();
    this.isWiFiDirect = new Boolean();
    this.networkKind = new WiFiNetworkKind();
    this.networkRssiInDecibelMilliwatts = new Number();
    this.phyKind = new WiFiPhyKind();
    this.securitySettings = new Object();
    this.signalBars = new Number();
    this.ssid = new String();
    this.uptime = new Number();
  };
  

  return cls;
}) ();
exports.WiFiAvailableNetwork = WiFiAvailableNetwork;

WiFiConnectionResult = (function () {
  var cls = function WiFiConnectionResult() {
    this.connectionStatus = new WiFiConnectionStatus();
  };
  

  return cls;
}) ();
exports.WiFiConnectionResult = WiFiConnectionResult;


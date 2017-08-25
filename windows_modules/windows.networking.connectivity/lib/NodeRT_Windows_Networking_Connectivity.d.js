  
NetworkUsageStates = (function () {
  var cls = function NetworkUsageStates() {
      this.roaming = new TriStates();
      this.shared = new TriStates();
    };
  return cls;
}) ();
exports.NetworkUsageStates = NetworkUsageStates;


  
WwanContract = (function () {
  var cls = function WwanContract() {
    };
  return cls;
}) ();
exports.WwanContract = WwanContract;


_NetworkCostType = function () {
  this.unknown = 0;
  this.unrestricted = 1;
  this.fixed = 2;
  this.variable = 3;
}
exports.NetworkCostType = new _NetworkCostType();

_NetworkConnectivityLevel = function () {
  this.none = 0;
  this.localAccess = 1;
  this.constrainedInternetAccess = 2;
  this.internetAccess = 3;
}
exports.NetworkConnectivityLevel = new _NetworkConnectivityLevel();

_NetworkTypes = function () {
  this.none = 0;
  this.internet = 1;
  this.privateNetwork = 2;
}
exports.NetworkTypes = new _NetworkTypes();

_RoamingStates = function () {
  this.none = 0;
  this.notRoaming = 1;
  this.roaming = 2;
}
exports.RoamingStates = new _RoamingStates();

_NetworkAuthenticationType = function () {
  this.none = 0;
  this.unknown = 1;
  this.open80211 = 2;
  this.sharedKey80211 = 3;
  this.wpa = 4;
  this.wpaPsk = 5;
  this.wpaNone = 6;
  this.rsna = 7;
  this.rsnaPsk = 8;
  this.ihv = 9;
}
exports.NetworkAuthenticationType = new _NetworkAuthenticationType();

_NetworkEncryptionType = function () {
  this.none = 0;
  this.unknown = 1;
  this.wep = 2;
  this.wep40 = 3;
  this.wep104 = 4;
  this.tkip = 5;
  this.ccmp = 6;
  this.wpaUseGroup = 7;
  this.rsnUseGroup = 8;
  this.ihv = 9;
}
exports.NetworkEncryptionType = new _NetworkEncryptionType();

_DomainConnectivityLevel = function () {
  this.none = 0;
  this.unauthenticated = 1;
  this.authenticated = 2;
}
exports.DomainConnectivityLevel = new _DomainConnectivityLevel();

_DataUsageGranularity = function () {
  this.perMinute = 0;
  this.perHour = 1;
  this.perDay = 2;
  this.total = 3;
}
exports.DataUsageGranularity = new _DataUsageGranularity();

_CellularApnAuthenticationType = function () {
  this.none = 0;
  this.pap = 1;
  this.chap = 2;
  this.mschapv2 = 3;
}
exports.CellularApnAuthenticationType = new _CellularApnAuthenticationType();

_TriStates = function () {
  this.doNotCare = 0;
  this.no = 1;
  this.yes = 2;
}
exports.TriStates = new _TriStates();

_WwanNetworkRegistrationState = function () {
  this.none = 0;
  this.deregistered = 1;
  this.searching = 2;
  this.home = 3;
  this.roaming = 4;
  this.partner = 5;
  this.denied = 6;
}
exports.WwanNetworkRegistrationState = new _WwanNetworkRegistrationState();

_WwanDataClass = function () {
  this.none = 0;
  this.gprs = 1;
  this.edge = 2;
  this.umts = 3;
  this.hsdpa = 4;
  this.hsupa = 5;
  this.lteAdvanced = 6;
  this.cdma1xRtt = 7;
  this.cdma1xEvdo = 8;
  this.cdma1xEvdoRevA = 9;
  this.cdma1xEvdv = 10;
  this.cdma3xRtt = 11;
  this.cdma1xEvdoRevB = 12;
  this.cdmaUmb = 13;
  this.custom = 14;
}
exports.WwanDataClass = new _WwanDataClass();

IPInformation = (function () {
  var cls = function IPInformation() {
    this.networkAdapter = new NetworkAdapter();
    this.prefixLength = new Number();
  };
  

  return cls;
}) ();
exports.IPInformation = IPInformation;

DataPlanUsage = (function () {
  var cls = function DataPlanUsage() {
    this.lastSyncTime = new Date();
    this.megabytesUsed = new Number();
  };
  

  return cls;
}) ();
exports.DataPlanUsage = DataPlanUsage;

ConnectionCost = (function () {
  var cls = function ConnectionCost() {
    this.approachingDataLimit = new Boolean();
    this.networkCostType = new NetworkCostType();
    this.overDataLimit = new Boolean();
    this.roaming = new Boolean();
    this.backgroundDataUsageRestricted = new Boolean();
  };
  

  return cls;
}) ();
exports.ConnectionCost = ConnectionCost;

DataPlanStatus = (function () {
  var cls = function DataPlanStatus() {
    this.dataLimitInMegabytes = new Number();
    this.dataPlanUsage = new DataPlanUsage();
    this.inboundBitsPerSecond = new Number();
    this.maxTransferSizeInMegabytes = new Number();
    this.nextBillingCycle = new Date();
    this.outboundBitsPerSecond = new Number();
  };
  

  return cls;
}) ();
exports.DataPlanStatus = DataPlanStatus;

NetworkAdapter = (function () {
  var cls = function NetworkAdapter() {
    this.ianaInterfaceType = new Number();
    this.inboundMaxBitsPerSecond = new Number();
    this.networkAdapterId = new String();
    this.networkItem = new NetworkItem();
    this.outboundMaxBitsPerSecond = new Number();
  };
  

  cls.prototype.getConnectedProfileAsync = function getConnectedProfileAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.NetworkAdapter = NetworkAdapter;

DataUsage = (function () {
  var cls = function DataUsage() {
    this.bytesReceived = new Number();
    this.bytesSent = new Number();
  };
  

  return cls;
}) ();
exports.DataUsage = DataUsage;

NetworkSecuritySettings = (function () {
  var cls = function NetworkSecuritySettings() {
    this.networkAuthenticationType = new NetworkAuthenticationType();
    this.networkEncryptionType = new NetworkEncryptionType();
  };
  

  return cls;
}) ();
exports.NetworkSecuritySettings = NetworkSecuritySettings;

WlanConnectionProfileDetails = (function () {
  var cls = function WlanConnectionProfileDetails() {
  };
  

  cls.prototype.getConnectedSsid = function getConnectedSsid() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  return cls;
}) ();
exports.WlanConnectionProfileDetails = WlanConnectionProfileDetails;

NetworkUsage = (function () {
  var cls = function NetworkUsage() {
    this.bytesReceived = new Number();
    this.bytesSent = new Number();
    this.connectionDuration = new Number();
  };
  

  return cls;
}) ();
exports.NetworkUsage = NetworkUsage;

ConnectivityInterval = (function () {
  var cls = function ConnectivityInterval() {
    this.connectionDuration = new Number();
    this.startTime = new Date();
  };
  

  return cls;
}) ();
exports.ConnectivityInterval = ConnectivityInterval;

AttributedNetworkUsage = (function () {
  var cls = function AttributedNetworkUsage() {
    this.attributionId = new String();
    this.attributionName = new String();
    this.attributionThumbnail = new Object();
    this.bytesReceived = new Number();
    this.bytesSent = new Number();
  };
  

  return cls;
}) ();
exports.AttributedNetworkUsage = AttributedNetworkUsage;

LanIdentifierData = (function () {
  var cls = function LanIdentifierData() {
    this.type = new Number();
    this.value = new Object();
  };
  

  return cls;
}) ();
exports.LanIdentifierData = LanIdentifierData;

ConnectionProfile = (function () {
  var cls = function ConnectionProfile() {
    this.networkAdapter = new NetworkAdapter();
    this.networkSecuritySettings = new NetworkSecuritySettings();
    this.profileName = new String();
    this.isWlanConnectionProfile = new Boolean();
    this.isWwanConnectionProfile = new Boolean();
    this.serviceProviderGuid = new String();
    this.wlanConnectionProfileDetails = new WlanConnectionProfileDetails();
    this.wwanConnectionProfileDetails = new WwanConnectionProfileDetails();
  };
  

  cls.prototype.getNetworkUsageAsync = function getNetworkUsageAsync(startTime, endTime, granularity, states, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="startTime" type="Date">A param.</param>
    /// <param name="endTime" type="Date">A param.</param>
    /// <param name="granularity" type="DataUsageGranularity">A param.</param>
    /// <param name="states" type="NetworkUsageStates">A param.</param>
    /// </signature>
  }


  cls.prototype.getConnectivityIntervalsAsync = function getConnectivityIntervalsAsync(startTime, endTime, states, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="startTime" type="Date">A param.</param>
    /// <param name="endTime" type="Date">A param.</param>
    /// <param name="states" type="NetworkUsageStates">A param.</param>
    /// </signature>
  }


  cls.prototype.getAttributedNetworkUsageAsync = function getAttributedNetworkUsageAsync(startTime, endTime, states, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="startTime" type="Date">A param.</param>
    /// <param name="endTime" type="Date">A param.</param>
    /// <param name="states" type="NetworkUsageStates">A param.</param>
    /// </signature>
  }


  cls.prototype.getNetworkConnectivityLevel = function getNetworkConnectivityLevel() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="NetworkConnectivityLevel" />
    /// </signature>
    return new NetworkConnectivityLevel();
  }


  cls.prototype.getNetworkNames = function getNetworkNames() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.getConnectionCost = function getConnectionCost() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="ConnectionCost" />
    /// </signature>
    return new ConnectionCost();
  }


  cls.prototype.getDataPlanStatus = function getDataPlanStatus() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="DataPlanStatus" />
    /// </signature>
    return new DataPlanStatus();
  }


  cls.prototype.getLocalUsage = function getLocalUsage(StartTime, EndTime) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="StartTime" type="Date">A param.</param>
    /// <param name="EndTime" type="Date">A param.</param>
    /// <returns type="DataUsage" />
    /// </signature>
    return new DataUsage();
  }

cls.prototype.getLocalUsage = function getLocalUsage(StartTime, EndTime, States) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="StartTime" type="Date">A param.</param>
    /// <param name="EndTime" type="Date">A param.</param>
    /// <param name="States" type="RoamingStates">A param.</param>
    /// <returns type="DataUsage" />
    /// </signature>
    return new DataUsage();
  }


  cls.prototype.getSignalBars = function getSignalBars() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.getDomainConnectivityLevel = function getDomainConnectivityLevel() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="DomainConnectivityLevel" />
    /// </signature>
    return new DomainConnectivityLevel();
  }


  return cls;
}) ();
exports.ConnectionProfile = ConnectionProfile;

LanIdentifier = (function () {
  var cls = function LanIdentifier() {
    this.infrastructureId = new LanIdentifierData();
    this.networkAdapterId = new String();
    this.portId = new LanIdentifierData();
  };
  

  return cls;
}) ();
exports.LanIdentifier = LanIdentifier;

ProxyConfiguration = (function () {
  var cls = function ProxyConfiguration() {
    this.canConnectDirectly = new Boolean();
    this.proxyUris = new Object();
  };
  

  return cls;
}) ();
exports.ProxyConfiguration = ProxyConfiguration;

ConnectionProfileFilter = (function () {
  var cls = function ConnectionProfileFilter() {
    this.serviceProviderGuid = new String();
    this.networkCostType = new NetworkCostType();
    this.isWwanConnectionProfile = new Boolean();
    this.isWlanConnectionProfile = new Boolean();
    this.isConnected = new Boolean();
    this.isRoaming = new Boolean();
    this.isOverDataLimit = new Boolean();
    this.isBackgroundDataUsageRestricted = new Boolean();
    this.rawData = new Object();
  };
  

  return cls;
}) ();
exports.ConnectionProfileFilter = ConnectionProfileFilter;

NetworkItem = (function () {
  var cls = function NetworkItem() {
    this.networkId = new String();
  };
  

  cls.prototype.getNetworkTypes = function getNetworkTypes() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="NetworkTypes" />
    /// </signature>
    return new NetworkTypes();
  }


  return cls;
}) ();
exports.NetworkItem = NetworkItem;

RoutePolicy = (function () {
  var cls = function RoutePolicy() {
    this.connectionProfile = new ConnectionProfile();
    this.hostName = new Object();
    this.hostNameType = new Number();
  };
  
var cls = function RoutePolicy(connectionProfile, hostName, type) {
      this.connectionProfile = new ConnectionProfile();
      this.hostName = new Object();
      this.hostNameType = new Number();
};


  return cls;
}) ();
exports.RoutePolicy = RoutePolicy;

CellularApnContext = (function () {
  var cls = function CellularApnContext() {
    this.userName = new String();
    this.providerId = new String();
    this.password = new String();
    this.isCompressionEnabled = new Boolean();
    this.authenticationType = new CellularApnAuthenticationType();
    this.accessPointName = new String();
  };
  

  return cls;
}) ();
exports.CellularApnContext = CellularApnContext;

ConnectionSession = (function () {
  var cls = function ConnectionSession() {
    this.connectionProfile = new ConnectionProfile();
  };
  

  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.ConnectionSession = ConnectionSession;

NetworkInformation = (function () {
  var cls = function NetworkInformation() {
  };
  

  cls.findConnectionProfilesAsync = function findConnectionProfilesAsync(pProfileFilter, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pProfileFilter" type="ConnectionProfileFilter">A param.</param>
    /// </signature>
  }



  cls.getProxyConfigurationAsync = function getProxyConfigurationAsync(uri, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="uri" type="Object">A param.</param>
    /// </signature>
  }



  cls.getConnectionProfiles = function getConnectionProfiles() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.getInternetConnectionProfile = function getInternetConnectionProfile() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="ConnectionProfile" />
    /// </signature>
    return new ConnectionProfile();
  }


  cls.getLanIdentifiers = function getLanIdentifiers() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.getHostNames = function getHostNames() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.getSortedEndpointPairs = function getSortedEndpointPairs(destinationList, sortOptions) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destinationList" type="Object">A param.</param>
    /// <param name="sortOptions" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.NetworkInformation = NetworkInformation;

ConnectivityManager = (function () {
  var cls = function ConnectivityManager() {
  };
  

  cls.acquireConnectionAsync = function acquireConnectionAsync(cellularApnContext, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="cellularApnContext" type="CellularApnContext">A param.</param>
    /// </signature>
  }



  cls.addHttpRoutePolicy = function addHttpRoutePolicy(routePolicy) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="routePolicy" type="RoutePolicy">A param.</param>
    /// </signature>
  }


  cls.removeHttpRoutePolicy = function removeHttpRoutePolicy(routePolicy) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="routePolicy" type="RoutePolicy">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.ConnectivityManager = ConnectivityManager;

NetworkStateChangeEventDetails = (function () {
  var cls = function NetworkStateChangeEventDetails() {
    this.hasNewConnectionCost = new Boolean();
    this.hasNewDomainConnectivityLevel = new Boolean();
    this.hasNewHostNameList = new Boolean();
    this.hasNewInternetConnectionProfile = new Boolean();
    this.hasNewNetworkConnectivityLevel = new Boolean();
    this.hasNewWwanRegistrationState = new Boolean();
    this.hasNewTetheringClientCount = new Boolean();
    this.hasNewTetheringOperationalState = new Boolean();
  };
  

  return cls;
}) ();
exports.NetworkStateChangeEventDetails = NetworkStateChangeEventDetails;

WwanConnectionProfileDetails = (function () {
  var cls = function WwanConnectionProfileDetails() {
    this.accessPointName = new String();
    this.homeProviderId = new String();
  };
  

  cls.prototype.getNetworkRegistrationState = function getNetworkRegistrationState() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="WwanNetworkRegistrationState" />
    /// </signature>
    return new WwanNetworkRegistrationState();
  }


  cls.prototype.getCurrentDataClass = function getCurrentDataClass() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="WwanDataClass" />
    /// </signature>
    return new WwanDataClass();
  }


  return cls;
}) ();
exports.WwanConnectionProfileDetails = WwanConnectionProfileDetails;


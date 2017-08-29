_KeyCredentialStatus = function () {
  this.success = 0;
  this.unknownError = 1;
  this.notFound = 2;
  this.userCanceled = 3;
  this.userPrefersPassword = 4;
  this.credentialAlreadyExists = 5;
  this.securityDeviceLocked = 6;
}
exports.KeyCredentialStatus = new _KeyCredentialStatus();

_KeyCredentialAttestationStatus = function () {
  this.success = 0;
  this.unknownError = 1;
  this.notSupported = 2;
  this.temporaryFailure = 3;
}
exports.KeyCredentialAttestationStatus = new _KeyCredentialAttestationStatus();

_KeyCredentialCreationOption = function () {
  this.replaceExisting = 0;
  this.failIfExists = 1;
}
exports.KeyCredentialCreationOption = new _KeyCredentialCreationOption();

_WebAccountState = function () {
  this.none = 0;
  this.connected = 1;
  this.error = 2;
}
exports.WebAccountState = new _WebAccountState();

_WebAccountPictureSize = function () {
  this.size64x64 = 0;
  this.size208x208 = 1;
  this.size424x424 = 2;
  this.size1080x1080 = 3;
}
exports.WebAccountPictureSize = new _WebAccountPictureSize();

KeyCredentialRetrievalResult = (function () {
  var cls = function KeyCredentialRetrievalResult() {
    this.credential = new KeyCredential();
    this.status = new KeyCredentialStatus();
  };
  

  return cls;
}) ();
exports.KeyCredentialRetrievalResult = KeyCredentialRetrievalResult;

KeyCredentialOperationResult = (function () {
  var cls = function KeyCredentialOperationResult() {
    this.result = new Object();
    this.status = new KeyCredentialStatus();
  };
  

  return cls;
}) ();
exports.KeyCredentialOperationResult = KeyCredentialOperationResult;

KeyCredentialAttestationResult = (function () {
  var cls = function KeyCredentialAttestationResult() {
    this.attestationBuffer = new Object();
    this.certificateChainBuffer = new Object();
    this.status = new KeyCredentialAttestationStatus();
  };
  

  return cls;
}) ();
exports.KeyCredentialAttestationResult = KeyCredentialAttestationResult;

KeyCredential = (function () {
  var cls = function KeyCredential() {
    this.name = new String();
  };
  

  cls.prototype.requestSignAsync = function requestSignAsync(data, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="data" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.getAttestationAsync = function getAttestationAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.retrievePublicKey = function retrievePublicKey() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }

cls.prototype.retrievePublicKey = function retrievePublicKey(blobType) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="blobType" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.KeyCredential = KeyCredential;

KeyCredentialManager = (function () {
  var cls = function KeyCredentialManager() {
  };
  

  cls.isSupportedAsync = function isSupportedAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }



  cls.renewAttestationAsync = function renewAttestationAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }



  cls.requestCreateAsync = function requestCreateAsync(name, option, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="name" type="String">A param.</param>
    /// <param name="option" type="KeyCredentialCreationOption">A param.</param>
    /// </signature>
  }



  cls.openAsync = function openAsync(name, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="name" type="String">A param.</param>
    /// </signature>
  }



  cls.deleteAsync = function deleteAsync(name, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="name" type="String">A param.</param>
    /// </signature>
  }



  return cls;
}) ();
exports.KeyCredentialManager = KeyCredentialManager;

WebAccountProvider = (function () {
  var cls = function WebAccountProvider() {
    this.displayName = new String();
    this.iconUri = new Object();
    this.id = new String();
    this.authority = new String();
    this.displayPurpose = new String();
    this.user = new Object();
  };
  
var cls = function WebAccountProvider(id, displayName, iconUri) {
      this.displayName = new String();
      this.iconUri = new Object();
      this.id = new String();
      this.authority = new String();
      this.displayPurpose = new String();
      this.user = new Object();
};


  return cls;
}) ();
exports.WebAccountProvider = WebAccountProvider;

WebAccount = (function () {
  var cls = function WebAccount() {
    this.state = new WebAccountState();
    this.userName = new String();
    this.webAccountProvider = new WebAccountProvider();
    this.id = new String();
    this.properties = new Object();
  };
  
var cls = function WebAccount(webAccountProvider, userName, state) {
      this.state = new WebAccountState();
      this.userName = new String();
      this.webAccountProvider = new WebAccountProvider();
      this.id = new String();
      this.properties = new Object();
};


  cls.prototype.getPictureAsync = function getPictureAsync(desizedSize, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desizedSize" type="WebAccountPictureSize">A param.</param>
    /// </signature>
  }


  cls.prototype.signOutAsync = function signOutAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.signOutAsync = function signOutAsync(clientId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="clientId" type="String">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.WebAccount = WebAccount;

IWebAccount = (function () {
  var cls = function IWebAccount() {
    this.state = new WebAccountState();
    this.userName = new String();
    this.webAccountProvider = new WebAccountProvider();
  };
  

  return cls;
}) ();
exports.IWebAccount = IWebAccount;

PasswordCredential = (function () {
  var cls = function PasswordCredential() {
    this.userName = new String();
    this.resource = new String();
    this.password = new String();
    this.properties = new Object();
  };
  
var cls = function PasswordCredential(resource, userName, password) {
      this.userName = new String();
      this.resource = new String();
      this.password = new String();
      this.properties = new Object();
};


  cls.prototype.retrievePassword = function retrievePassword() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.PasswordCredential = PasswordCredential;

PasswordVault = (function () {
  var cls = function PasswordVault() {
  };
  

  cls.prototype.add = function add(credential) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="credential" type="PasswordCredential">A param.</param>
    /// </signature>
  }


  cls.prototype.remove = function remove(credential) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="credential" type="PasswordCredential">A param.</param>
    /// </signature>
  }


  cls.prototype.retrieve = function retrieve(resource, userName) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="resource" type="String">A param.</param>
    /// <param name="userName" type="String">A param.</param>
    /// <returns type="PasswordCredential" />
    /// </signature>
    return new PasswordCredential();
  }


  cls.prototype.findAllByResource = function findAllByResource(resource) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="resource" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.findAllByUserName = function findAllByUserName(userName) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="userName" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.retrieveAll = function retrieveAll() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.PasswordVault = PasswordVault;

PasswordCredentialPropertyStore = (function () {
  var cls = function PasswordCredentialPropertyStore() {
  };
  

  cls.prototype.lookup = function lookup(key) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.hasKey = function hasKey(key) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.prototype.getView = function getView() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.insert = function insert(key, value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// <param name="value" type="Object">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.prototype.remove = function remove(key) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.clear = function clear() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.first = function first() {
    /// <signature>
    /// <summary>Function summary.</summary>
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
exports.PasswordCredentialPropertyStore = PasswordCredentialPropertyStore;


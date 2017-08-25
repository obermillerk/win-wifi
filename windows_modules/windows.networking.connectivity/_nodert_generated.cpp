// Copyright (c) Microsoft Corporation
// All rights reserved. 
//
// Licensed under the Apache License, Version 2.0 (the ""License""); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 
//
// THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT. 
//
// See the Apache Version 2.0 License for specific language governing permissions and limitations under the License.

// TODO: Verify that this is is still needed..
#define NTDDI_VERSION 0x06010000

#include <v8.h>
#include "nan.h"
#include <string>
#include <ppltasks.h>
#include "CollectionsConverter.h"
#include "CollectionsWrap.h"
#include "node-async.h"
#include "NodeRtUtils.h"
#include "OpaqueWrapper.h"
#include "WrapperBase.h"

#using <Windows.WinMD>

// this undefs fixes the issues of compiling Windows.Data.Json, Windows.Storag.FileProperties, and Windows.Stroage.Search
// Some of the node header files brings windows definitions with the same names as some of the WinRT methods
#undef DocumentProperties
#undef GetObject
#undef CreateEvent
#undef FindText
#undef SendMessage

const char* REGISTRATION_TOKEN_MAP_PROPERTY_NAME = "__registrationTokenMap__";

using v8::Array;
using v8::String;
using v8::Handle;
using v8::Value;
using v8::Boolean;
using v8::Integer;
using v8::FunctionTemplate;
using v8::Object;
using v8::Local;
using v8::Function;
using v8::Date;
using v8::Number;
using v8::PropertyAttribute;
using v8::Primitive;
using Nan::HandleScope;
using Nan::Persistent;
using Nan::Undefined;
using Nan::True;
using Nan::False;
using Nan::Null;
using Nan::MaybeLocal;
using Nan::EscapableHandleScope;
using Nan::HandleScope;
using Nan::TryCatch;
using namespace concurrency;

namespace NodeRT { namespace Windows { namespace Networking { namespace Connectivity { 

  v8::Local<v8::Value> WrapIPInformation(::Windows::Networking::Connectivity::IPInformation^ wintRtInstance);
  ::Windows::Networking::Connectivity::IPInformation^ UnwrapIPInformation(Local<Value> value);
  
  v8::Local<v8::Value> WrapDataPlanUsage(::Windows::Networking::Connectivity::DataPlanUsage^ wintRtInstance);
  ::Windows::Networking::Connectivity::DataPlanUsage^ UnwrapDataPlanUsage(Local<Value> value);
  
  v8::Local<v8::Value> WrapConnectionCost(::Windows::Networking::Connectivity::ConnectionCost^ wintRtInstance);
  ::Windows::Networking::Connectivity::ConnectionCost^ UnwrapConnectionCost(Local<Value> value);
  
  v8::Local<v8::Value> WrapDataPlanStatus(::Windows::Networking::Connectivity::DataPlanStatus^ wintRtInstance);
  ::Windows::Networking::Connectivity::DataPlanStatus^ UnwrapDataPlanStatus(Local<Value> value);
  
  v8::Local<v8::Value> WrapNetworkAdapter(::Windows::Networking::Connectivity::NetworkAdapter^ wintRtInstance);
  ::Windows::Networking::Connectivity::NetworkAdapter^ UnwrapNetworkAdapter(Local<Value> value);
  
  v8::Local<v8::Value> WrapDataUsage(::Windows::Networking::Connectivity::DataUsage^ wintRtInstance);
  ::Windows::Networking::Connectivity::DataUsage^ UnwrapDataUsage(Local<Value> value);
  
  v8::Local<v8::Value> WrapNetworkSecuritySettings(::Windows::Networking::Connectivity::NetworkSecuritySettings^ wintRtInstance);
  ::Windows::Networking::Connectivity::NetworkSecuritySettings^ UnwrapNetworkSecuritySettings(Local<Value> value);
  
  v8::Local<v8::Value> WrapWlanConnectionProfileDetails(::Windows::Networking::Connectivity::WlanConnectionProfileDetails^ wintRtInstance);
  ::Windows::Networking::Connectivity::WlanConnectionProfileDetails^ UnwrapWlanConnectionProfileDetails(Local<Value> value);
  
  v8::Local<v8::Value> WrapNetworkUsage(::Windows::Networking::Connectivity::NetworkUsage^ wintRtInstance);
  ::Windows::Networking::Connectivity::NetworkUsage^ UnwrapNetworkUsage(Local<Value> value);
  
  v8::Local<v8::Value> WrapConnectivityInterval(::Windows::Networking::Connectivity::ConnectivityInterval^ wintRtInstance);
  ::Windows::Networking::Connectivity::ConnectivityInterval^ UnwrapConnectivityInterval(Local<Value> value);
  
  v8::Local<v8::Value> WrapAttributedNetworkUsage(::Windows::Networking::Connectivity::AttributedNetworkUsage^ wintRtInstance);
  ::Windows::Networking::Connectivity::AttributedNetworkUsage^ UnwrapAttributedNetworkUsage(Local<Value> value);
  
  v8::Local<v8::Value> WrapLanIdentifierData(::Windows::Networking::Connectivity::LanIdentifierData^ wintRtInstance);
  ::Windows::Networking::Connectivity::LanIdentifierData^ UnwrapLanIdentifierData(Local<Value> value);
  
  v8::Local<v8::Value> WrapConnectionProfile(::Windows::Networking::Connectivity::ConnectionProfile^ wintRtInstance);
  ::Windows::Networking::Connectivity::ConnectionProfile^ UnwrapConnectionProfile(Local<Value> value);
  
  v8::Local<v8::Value> WrapLanIdentifier(::Windows::Networking::Connectivity::LanIdentifier^ wintRtInstance);
  ::Windows::Networking::Connectivity::LanIdentifier^ UnwrapLanIdentifier(Local<Value> value);
  
  v8::Local<v8::Value> WrapProxyConfiguration(::Windows::Networking::Connectivity::ProxyConfiguration^ wintRtInstance);
  ::Windows::Networking::Connectivity::ProxyConfiguration^ UnwrapProxyConfiguration(Local<Value> value);
  
  v8::Local<v8::Value> WrapConnectionProfileFilter(::Windows::Networking::Connectivity::ConnectionProfileFilter^ wintRtInstance);
  ::Windows::Networking::Connectivity::ConnectionProfileFilter^ UnwrapConnectionProfileFilter(Local<Value> value);
  
  v8::Local<v8::Value> WrapNetworkItem(::Windows::Networking::Connectivity::NetworkItem^ wintRtInstance);
  ::Windows::Networking::Connectivity::NetworkItem^ UnwrapNetworkItem(Local<Value> value);
  
  v8::Local<v8::Value> WrapRoutePolicy(::Windows::Networking::Connectivity::RoutePolicy^ wintRtInstance);
  ::Windows::Networking::Connectivity::RoutePolicy^ UnwrapRoutePolicy(Local<Value> value);
  
  v8::Local<v8::Value> WrapCellularApnContext(::Windows::Networking::Connectivity::CellularApnContext^ wintRtInstance);
  ::Windows::Networking::Connectivity::CellularApnContext^ UnwrapCellularApnContext(Local<Value> value);
  
  v8::Local<v8::Value> WrapConnectionSession(::Windows::Networking::Connectivity::ConnectionSession^ wintRtInstance);
  ::Windows::Networking::Connectivity::ConnectionSession^ UnwrapConnectionSession(Local<Value> value);
  
  v8::Local<v8::Value> WrapNetworkInformation(::Windows::Networking::Connectivity::NetworkInformation^ wintRtInstance);
  ::Windows::Networking::Connectivity::NetworkInformation^ UnwrapNetworkInformation(Local<Value> value);
  
  v8::Local<v8::Value> WrapConnectivityManager(::Windows::Networking::Connectivity::ConnectivityManager^ wintRtInstance);
  ::Windows::Networking::Connectivity::ConnectivityManager^ UnwrapConnectivityManager(Local<Value> value);
  
  v8::Local<v8::Value> WrapNetworkStateChangeEventDetails(::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^ wintRtInstance);
  ::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^ UnwrapNetworkStateChangeEventDetails(Local<Value> value);
  
  v8::Local<v8::Value> WrapWwanConnectionProfileDetails(::Windows::Networking::Connectivity::WwanConnectionProfileDetails^ wintRtInstance);
  ::Windows::Networking::Connectivity::WwanConnectionProfileDetails^ UnwrapWwanConnectionProfileDetails(Local<Value> value);
  


  static void InitNetworkCostTypeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("NetworkCostType").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("unknown").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkCostType::Unknown)));
	Nan::Set(enumObject, Nan::New<String>("unrestricted").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkCostType::Unrestricted)));
	Nan::Set(enumObject, Nan::New<String>("fixed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkCostType::Fixed)));
	Nan::Set(enumObject, Nan::New<String>("variable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkCostType::Variable)));
  }


  static void InitNetworkConnectivityLevelEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("NetworkConnectivityLevel").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkConnectivityLevel::None)));
	Nan::Set(enumObject, Nan::New<String>("localAccess").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkConnectivityLevel::LocalAccess)));
	Nan::Set(enumObject, Nan::New<String>("constrainedInternetAccess").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkConnectivityLevel::ConstrainedInternetAccess)));
	Nan::Set(enumObject, Nan::New<String>("internetAccess").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkConnectivityLevel::InternetAccess)));
  }


  static void InitNetworkTypesEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("NetworkTypes").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkTypes::None)));
	Nan::Set(enumObject, Nan::New<String>("internet").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkTypes::Internet)));
	Nan::Set(enumObject, Nan::New<String>("privateNetwork").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkTypes::PrivateNetwork)));
  }


  static void InitRoamingStatesEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("RoamingStates").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::RoamingStates::None)));
	Nan::Set(enumObject, Nan::New<String>("notRoaming").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::RoamingStates::NotRoaming)));
	Nan::Set(enumObject, Nan::New<String>("roaming").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::RoamingStates::Roaming)));
  }


  static void InitNetworkAuthenticationTypeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("NetworkAuthenticationType").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkAuthenticationType::None)));
	Nan::Set(enumObject, Nan::New<String>("unknown").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkAuthenticationType::Unknown)));
	Nan::Set(enumObject, Nan::New<String>("open80211").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkAuthenticationType::Open80211)));
	Nan::Set(enumObject, Nan::New<String>("sharedKey80211").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkAuthenticationType::SharedKey80211)));
	Nan::Set(enumObject, Nan::New<String>("wpa").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkAuthenticationType::Wpa)));
	Nan::Set(enumObject, Nan::New<String>("wpaPsk").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkAuthenticationType::WpaPsk)));
	Nan::Set(enumObject, Nan::New<String>("wpaNone").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkAuthenticationType::WpaNone)));
	Nan::Set(enumObject, Nan::New<String>("rsna").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkAuthenticationType::Rsna)));
	Nan::Set(enumObject, Nan::New<String>("rsnaPsk").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkAuthenticationType::RsnaPsk)));
	Nan::Set(enumObject, Nan::New<String>("ihv").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkAuthenticationType::Ihv)));
  }


  static void InitNetworkEncryptionTypeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("NetworkEncryptionType").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkEncryptionType::None)));
	Nan::Set(enumObject, Nan::New<String>("unknown").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkEncryptionType::Unknown)));
	Nan::Set(enumObject, Nan::New<String>("wep").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkEncryptionType::Wep)));
	Nan::Set(enumObject, Nan::New<String>("wep40").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkEncryptionType::Wep40)));
	Nan::Set(enumObject, Nan::New<String>("wep104").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkEncryptionType::Wep104)));
	Nan::Set(enumObject, Nan::New<String>("tkip").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkEncryptionType::Tkip)));
	Nan::Set(enumObject, Nan::New<String>("ccmp").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkEncryptionType::Ccmp)));
	Nan::Set(enumObject, Nan::New<String>("wpaUseGroup").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkEncryptionType::WpaUseGroup)));
	Nan::Set(enumObject, Nan::New<String>("rsnUseGroup").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkEncryptionType::RsnUseGroup)));
	Nan::Set(enumObject, Nan::New<String>("ihv").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::NetworkEncryptionType::Ihv)));
  }


  static void InitDomainConnectivityLevelEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("DomainConnectivityLevel").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::DomainConnectivityLevel::None)));
	Nan::Set(enumObject, Nan::New<String>("unauthenticated").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::DomainConnectivityLevel::Unauthenticated)));
	Nan::Set(enumObject, Nan::New<String>("authenticated").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::DomainConnectivityLevel::Authenticated)));
  }


  static void InitDataUsageGranularityEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("DataUsageGranularity").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("perMinute").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::DataUsageGranularity::PerMinute)));
	Nan::Set(enumObject, Nan::New<String>("perHour").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::DataUsageGranularity::PerHour)));
	Nan::Set(enumObject, Nan::New<String>("perDay").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::DataUsageGranularity::PerDay)));
	Nan::Set(enumObject, Nan::New<String>("total").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::DataUsageGranularity::Total)));
  }


  static void InitCellularApnAuthenticationTypeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("CellularApnAuthenticationType").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::CellularApnAuthenticationType::None)));
	Nan::Set(enumObject, Nan::New<String>("pap").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::CellularApnAuthenticationType::Pap)));
	Nan::Set(enumObject, Nan::New<String>("chap").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::CellularApnAuthenticationType::Chap)));
	Nan::Set(enumObject, Nan::New<String>("mschapv2").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::CellularApnAuthenticationType::Mschapv2)));
  }


  static void InitTriStatesEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("TriStates").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("doNotCare").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::TriStates::DoNotCare)));
	Nan::Set(enumObject, Nan::New<String>("no").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::TriStates::No)));
	Nan::Set(enumObject, Nan::New<String>("yes").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::TriStates::Yes)));
  }


  static void InitWwanNetworkRegistrationStateEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("WwanNetworkRegistrationState").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanNetworkRegistrationState::None)));
	Nan::Set(enumObject, Nan::New<String>("deregistered").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanNetworkRegistrationState::Deregistered)));
	Nan::Set(enumObject, Nan::New<String>("searching").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanNetworkRegistrationState::Searching)));
	Nan::Set(enumObject, Nan::New<String>("home").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanNetworkRegistrationState::Home)));
	Nan::Set(enumObject, Nan::New<String>("roaming").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanNetworkRegistrationState::Roaming)));
	Nan::Set(enumObject, Nan::New<String>("partner").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanNetworkRegistrationState::Partner)));
	Nan::Set(enumObject, Nan::New<String>("denied").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanNetworkRegistrationState::Denied)));
  }


  static void InitWwanDataClassEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("WwanDataClass").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanDataClass::None)));
	Nan::Set(enumObject, Nan::New<String>("gprs").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanDataClass::Gprs)));
	Nan::Set(enumObject, Nan::New<String>("edge").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanDataClass::Edge)));
	Nan::Set(enumObject, Nan::New<String>("umts").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanDataClass::Umts)));
	Nan::Set(enumObject, Nan::New<String>("hsdpa").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanDataClass::Hsdpa)));
	Nan::Set(enumObject, Nan::New<String>("hsupa").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanDataClass::Hsupa)));
	Nan::Set(enumObject, Nan::New<String>("lteAdvanced").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanDataClass::LteAdvanced)));
	Nan::Set(enumObject, Nan::New<String>("cdma1xRtt").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanDataClass::Cdma1xRtt)));
	Nan::Set(enumObject, Nan::New<String>("cdma1xEvdo").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanDataClass::Cdma1xEvdo)));
	Nan::Set(enumObject, Nan::New<String>("cdma1xEvdoRevA").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanDataClass::Cdma1xEvdoRevA)));
	Nan::Set(enumObject, Nan::New<String>("cdma1xEvdv").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanDataClass::Cdma1xEvdv)));
	Nan::Set(enumObject, Nan::New<String>("cdma3xRtt").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanDataClass::Cdma3xRtt)));
	Nan::Set(enumObject, Nan::New<String>("cdma1xEvdoRevB").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanDataClass::Cdma1xEvdoRevB)));
	Nan::Set(enumObject, Nan::New<String>("cdmaUmb").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanDataClass::CdmaUmb)));
	Nan::Set(enumObject, Nan::New<String>("custom").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Networking::Connectivity::WwanDataClass::Custom)));
  }



  
  static bool IsNetworkUsageStatesJsObject(Local<Value> value)
  {
    if (!value->IsObject())
    {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    symbol = Nan::New<String>("roaming").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsInt32())
      {
          return false;
      }
    }
    
    symbol = Nan::New<String>("shared").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsInt32())
      {
          return false;
      }
    }
    
    return true;
  }

  ::Windows::Networking::Connectivity::NetworkUsageStates NetworkUsageStatesFromJsObject(Local<Value> value)
  {
    HandleScope scope;
    ::Windows::Networking::Connectivity::NetworkUsageStates returnValue;
    
    if (!value->IsObject())
    {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    symbol = Nan::New<String>("roaming").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      returnValue.Roaming = static_cast<::Windows::Networking::Connectivity::TriStates>(Nan::To<int32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("shared").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      returnValue.Shared = static_cast<::Windows::Networking::Connectivity::TriStates>(Nan::To<int32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    return returnValue;
  }

  Local<Value> NetworkUsageStatesToJsObject(::Windows::Networking::Connectivity::NetworkUsageStates value)
  {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    Nan::Set(obj, Nan::New<String>("roaming").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(value.Roaming)));
    Nan::Set(obj, Nan::New<String>("shared").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(value.Shared)));
    
    return scope.Escape(obj);
  }

  
  static bool IsWwanContractJsObject(Local<Value> value)
  {
    if (!value->IsObject())
    {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::Networking::Connectivity::WwanContract WwanContractFromJsObject(Local<Value> value)
  {
    HandleScope scope;
    ::Windows::Networking::Connectivity::WwanContract returnValue;
    
    if (!value->IsObject())
    {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> WwanContractToJsObject(::Windows::Networking::Connectivity::WwanContract value)
  {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    
    return scope.Escape(obj);
  }

  
  class IPInformation : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IPInformation").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("networkAdapter").ToLocalChecked(), NetworkAdapterGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prefixLength").ToLocalChecked(), PrefixLengthGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IPInformation").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IPInformation(::Windows::Networking::Connectivity::IPInformation^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::IPInformation^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::IPInformation^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::IPInformation^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IPInformation *wrapperInstance = new IPInformation(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::IPInformation^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::IPInformation^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::IPInformation^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIPInformation(winRtInstance));
    }


  



    static void NetworkAdapterGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::IPInformation^>(info.This()))
      {
        return;
      }

      IPInformation *wrapper = IPInformation::Unwrap<IPInformation>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::NetworkAdapter^ result = wrapper->_instance->NetworkAdapter;
        info.GetReturnValue().Set(WrapNetworkAdapter(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PrefixLengthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::IPInformation^>(info.This()))
      {
        return;
      }

      IPInformation *wrapper = IPInformation::Unwrap<IPInformation>(info.This());

      try 
      {
        ::Platform::IBox<unsigned char>^ result = wrapper->_instance->PrefixLength;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::IPInformation^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIPInformation(::Windows::Networking::Connectivity::IPInformation^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::IPInformation^ UnwrapIPInformation(Local<Value> value);
  };
  Persistent<FunctionTemplate> IPInformation::s_constructorTemplate;

  v8::Local<v8::Value> WrapIPInformation(::Windows::Networking::Connectivity::IPInformation^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IPInformation::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::IPInformation^ UnwrapIPInformation(Local<Value> value)
  {
     return IPInformation::Unwrap<IPInformation>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIPInformation(Local<Object> exports)
  {
    IPInformation::Init(exports);
  }

  class DataPlanUsage : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DataPlanUsage").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastSyncTime").ToLocalChecked(), LastSyncTimeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("megabytesUsed").ToLocalChecked(), MegabytesUsedGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DataPlanUsage").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DataPlanUsage(::Windows::Networking::Connectivity::DataPlanUsage^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::DataPlanUsage^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataPlanUsage^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::DataPlanUsage^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      DataPlanUsage *wrapperInstance = new DataPlanUsage(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataPlanUsage^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::DataPlanUsage^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::DataPlanUsage^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDataPlanUsage(winRtInstance));
    }


  



    static void LastSyncTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataPlanUsage^>(info.This()))
      {
        return;
      }

      DataPlanUsage *wrapper = DataPlanUsage::Unwrap<DataPlanUsage>(info.This());

      try 
      {
        ::Windows::Foundation::DateTime result = wrapper->_instance->LastSyncTime;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MegabytesUsedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataPlanUsage^>(info.This()))
      {
        return;
      }

      DataPlanUsage *wrapper = DataPlanUsage::Unwrap<DataPlanUsage>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->MegabytesUsed;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::DataPlanUsage^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDataPlanUsage(::Windows::Networking::Connectivity::DataPlanUsage^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::DataPlanUsage^ UnwrapDataPlanUsage(Local<Value> value);
  };
  Persistent<FunctionTemplate> DataPlanUsage::s_constructorTemplate;

  v8::Local<v8::Value> WrapDataPlanUsage(::Windows::Networking::Connectivity::DataPlanUsage^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DataPlanUsage::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::DataPlanUsage^ UnwrapDataPlanUsage(Local<Value> value)
  {
     return DataPlanUsage::Unwrap<DataPlanUsage>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDataPlanUsage(Local<Object> exports)
  {
    DataPlanUsage::Init(exports);
  }

  class ConnectionCost : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ConnectionCost").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("approachingDataLimit").ToLocalChecked(), ApproachingDataLimitGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("networkCostType").ToLocalChecked(), NetworkCostTypeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("overDataLimit").ToLocalChecked(), OverDataLimitGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("roaming").ToLocalChecked(), RoamingGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("backgroundDataUsageRestricted").ToLocalChecked(), BackgroundDataUsageRestrictedGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("ConnectionCost").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ConnectionCost(::Windows::Networking::Connectivity::ConnectionCost^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::ConnectionCost^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionCost^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::ConnectionCost^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ConnectionCost *wrapperInstance = new ConnectionCost(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionCost^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::ConnectionCost^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::ConnectionCost^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapConnectionCost(winRtInstance));
    }


  



    static void ApproachingDataLimitGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionCost^>(info.This()))
      {
        return;
      }

      ConnectionCost *wrapper = ConnectionCost::Unwrap<ConnectionCost>(info.This());

      try 
      {
        bool result = wrapper->_instance->ApproachingDataLimit;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NetworkCostTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionCost^>(info.This()))
      {
        return;
      }

      ConnectionCost *wrapper = ConnectionCost::Unwrap<ConnectionCost>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::NetworkCostType result = wrapper->_instance->NetworkCostType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void OverDataLimitGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionCost^>(info.This()))
      {
        return;
      }

      ConnectionCost *wrapper = ConnectionCost::Unwrap<ConnectionCost>(info.This());

      try 
      {
        bool result = wrapper->_instance->OverDataLimit;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RoamingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionCost^>(info.This()))
      {
        return;
      }

      ConnectionCost *wrapper = ConnectionCost::Unwrap<ConnectionCost>(info.This());

      try 
      {
        bool result = wrapper->_instance->Roaming;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BackgroundDataUsageRestrictedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionCost^>(info.This()))
      {
        return;
      }

      ConnectionCost *wrapper = ConnectionCost::Unwrap<ConnectionCost>(info.This());

      try 
      {
        bool result = wrapper->_instance->BackgroundDataUsageRestricted;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::ConnectionCost^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapConnectionCost(::Windows::Networking::Connectivity::ConnectionCost^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::ConnectionCost^ UnwrapConnectionCost(Local<Value> value);
  };
  Persistent<FunctionTemplate> ConnectionCost::s_constructorTemplate;

  v8::Local<v8::Value> WrapConnectionCost(::Windows::Networking::Connectivity::ConnectionCost^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ConnectionCost::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::ConnectionCost^ UnwrapConnectionCost(Local<Value> value)
  {
     return ConnectionCost::Unwrap<ConnectionCost>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitConnectionCost(Local<Object> exports)
  {
    ConnectionCost::Init(exports);
  }

  class DataPlanStatus : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DataPlanStatus").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dataLimitInMegabytes").ToLocalChecked(), DataLimitInMegabytesGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dataPlanUsage").ToLocalChecked(), DataPlanUsageGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("inboundBitsPerSecond").ToLocalChecked(), InboundBitsPerSecondGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("maxTransferSizeInMegabytes").ToLocalChecked(), MaxTransferSizeInMegabytesGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nextBillingCycle").ToLocalChecked(), NextBillingCycleGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("outboundBitsPerSecond").ToLocalChecked(), OutboundBitsPerSecondGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DataPlanStatus").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DataPlanStatus(::Windows::Networking::Connectivity::DataPlanStatus^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::DataPlanStatus^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataPlanStatus^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::DataPlanStatus^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      DataPlanStatus *wrapperInstance = new DataPlanStatus(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataPlanStatus^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::DataPlanStatus^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::DataPlanStatus^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDataPlanStatus(winRtInstance));
    }


  



    static void DataLimitInMegabytesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataPlanStatus^>(info.This()))
      {
        return;
      }

      DataPlanStatus *wrapper = DataPlanStatus::Unwrap<DataPlanStatus>(info.This());

      try 
      {
        ::Platform::IBox<unsigned int>^ result = wrapper->_instance->DataLimitInMegabytes;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DataPlanUsageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataPlanStatus^>(info.This()))
      {
        return;
      }

      DataPlanStatus *wrapper = DataPlanStatus::Unwrap<DataPlanStatus>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::DataPlanUsage^ result = wrapper->_instance->DataPlanUsage;
        info.GetReturnValue().Set(WrapDataPlanUsage(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InboundBitsPerSecondGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataPlanStatus^>(info.This()))
      {
        return;
      }

      DataPlanStatus *wrapper = DataPlanStatus::Unwrap<DataPlanStatus>(info.This());

      try 
      {
        ::Platform::IBox<unsigned __int64>^ result = wrapper->_instance->InboundBitsPerSecond;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(static_cast<double>(result->Value))) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MaxTransferSizeInMegabytesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataPlanStatus^>(info.This()))
      {
        return;
      }

      DataPlanStatus *wrapper = DataPlanStatus::Unwrap<DataPlanStatus>(info.This());

      try 
      {
        ::Platform::IBox<unsigned int>^ result = wrapper->_instance->MaxTransferSizeInMegabytes;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NextBillingCycleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataPlanStatus^>(info.This()))
      {
        return;
      }

      DataPlanStatus *wrapper = DataPlanStatus::Unwrap<DataPlanStatus>(info.This());

      try 
      {
        ::Platform::IBox<::Windows::Foundation::DateTime>^ result = wrapper->_instance->NextBillingCycle;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(NodeRT::Utils::DateTimeToJS(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void OutboundBitsPerSecondGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataPlanStatus^>(info.This()))
      {
        return;
      }

      DataPlanStatus *wrapper = DataPlanStatus::Unwrap<DataPlanStatus>(info.This());

      try 
      {
        ::Platform::IBox<unsigned __int64>^ result = wrapper->_instance->OutboundBitsPerSecond;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(static_cast<double>(result->Value))) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::DataPlanStatus^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDataPlanStatus(::Windows::Networking::Connectivity::DataPlanStatus^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::DataPlanStatus^ UnwrapDataPlanStatus(Local<Value> value);
  };
  Persistent<FunctionTemplate> DataPlanStatus::s_constructorTemplate;

  v8::Local<v8::Value> WrapDataPlanStatus(::Windows::Networking::Connectivity::DataPlanStatus^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DataPlanStatus::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::DataPlanStatus^ UnwrapDataPlanStatus(Local<Value> value)
  {
     return DataPlanStatus::Unwrap<DataPlanStatus>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDataPlanStatus(Local<Object> exports)
  {
    DataPlanStatus::Init(exports);
  }

  class NetworkAdapter : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("NetworkAdapter").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "getConnectedProfileAsync", GetConnectedProfileAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("ianaInterfaceType").ToLocalChecked(), IanaInterfaceTypeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("inboundMaxBitsPerSecond").ToLocalChecked(), InboundMaxBitsPerSecondGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("networkAdapterId").ToLocalChecked(), NetworkAdapterIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("networkItem").ToLocalChecked(), NetworkItemGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("outboundMaxBitsPerSecond").ToLocalChecked(), OutboundMaxBitsPerSecondGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("NetworkAdapter").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    NetworkAdapter(::Windows::Networking::Connectivity::NetworkAdapter^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::NetworkAdapter^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkAdapter^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::NetworkAdapter^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      NetworkAdapter *wrapperInstance = new NetworkAdapter(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkAdapter^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::NetworkAdapter^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::NetworkAdapter^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapNetworkAdapter(winRtInstance));
    }


    static void GetConnectedProfileAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkAdapter^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      NetworkAdapter *wrapper = NetworkAdapter::Unwrap<NetworkAdapter>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Networking::Connectivity::ConnectionProfile^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetConnectedProfileAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Networking::Connectivity::ConnectionProfile^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = WrapConnectionProfile(result);
            if (tryCatch.HasCaught())
            {
              error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
            }
            else 
            {
              error = Undefined();
            }
            if (arg1.IsEmpty()) arg1 = Undefined();
            Local<Value> args[] = {error, arg1};
			// TODO: this is ugly! Needed due to the possibility of expception occuring inside object convertors
			// can be fixed by wrapping the conversion code in a function and calling it on the fly
			// we must clear the try catch block here so the invoked inner method exception won't get swollen (issue #52) 
			tryCatch.~TryCatch();

		    
            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  



    static void IanaInterfaceTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkAdapter^>(info.This()))
      {
        return;
      }

      NetworkAdapter *wrapper = NetworkAdapter::Unwrap<NetworkAdapter>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->IanaInterfaceType;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InboundMaxBitsPerSecondGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkAdapter^>(info.This()))
      {
        return;
      }

      NetworkAdapter *wrapper = NetworkAdapter::Unwrap<NetworkAdapter>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->InboundMaxBitsPerSecond;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NetworkAdapterIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkAdapter^>(info.This()))
      {
        return;
      }

      NetworkAdapter *wrapper = NetworkAdapter::Unwrap<NetworkAdapter>(info.This());

      try 
      {
        ::Platform::Guid result = wrapper->_instance->NetworkAdapterId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NetworkItemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkAdapter^>(info.This()))
      {
        return;
      }

      NetworkAdapter *wrapper = NetworkAdapter::Unwrap<NetworkAdapter>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::NetworkItem^ result = wrapper->_instance->NetworkItem;
        info.GetReturnValue().Set(WrapNetworkItem(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void OutboundMaxBitsPerSecondGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkAdapter^>(info.This()))
      {
        return;
      }

      NetworkAdapter *wrapper = NetworkAdapter::Unwrap<NetworkAdapter>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->OutboundMaxBitsPerSecond;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::NetworkAdapter^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapNetworkAdapter(::Windows::Networking::Connectivity::NetworkAdapter^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::NetworkAdapter^ UnwrapNetworkAdapter(Local<Value> value);
  };
  Persistent<FunctionTemplate> NetworkAdapter::s_constructorTemplate;

  v8::Local<v8::Value> WrapNetworkAdapter(::Windows::Networking::Connectivity::NetworkAdapter^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(NetworkAdapter::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::NetworkAdapter^ UnwrapNetworkAdapter(Local<Value> value)
  {
     return NetworkAdapter::Unwrap<NetworkAdapter>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitNetworkAdapter(Local<Object> exports)
  {
    NetworkAdapter::Init(exports);
  }

  class DataUsage : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DataUsage").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bytesReceived").ToLocalChecked(), BytesReceivedGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bytesSent").ToLocalChecked(), BytesSentGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("DataUsage").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DataUsage(::Windows::Networking::Connectivity::DataUsage^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::DataUsage^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataUsage^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::DataUsage^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      DataUsage *wrapperInstance = new DataUsage(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataUsage^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::DataUsage^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::DataUsage^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDataUsage(winRtInstance));
    }


  



    static void BytesReceivedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataUsage^>(info.This()))
      {
        return;
      }

      DataUsage *wrapper = DataUsage::Unwrap<DataUsage>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->BytesReceived;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BytesSentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::DataUsage^>(info.This()))
      {
        return;
      }

      DataUsage *wrapper = DataUsage::Unwrap<DataUsage>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->BytesSent;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::DataUsage^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDataUsage(::Windows::Networking::Connectivity::DataUsage^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::DataUsage^ UnwrapDataUsage(Local<Value> value);
  };
  Persistent<FunctionTemplate> DataUsage::s_constructorTemplate;

  v8::Local<v8::Value> WrapDataUsage(::Windows::Networking::Connectivity::DataUsage^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DataUsage::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::DataUsage^ UnwrapDataUsage(Local<Value> value)
  {
     return DataUsage::Unwrap<DataUsage>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDataUsage(Local<Object> exports)
  {
    DataUsage::Init(exports);
  }

  class NetworkSecuritySettings : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("NetworkSecuritySettings").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("networkAuthenticationType").ToLocalChecked(), NetworkAuthenticationTypeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("networkEncryptionType").ToLocalChecked(), NetworkEncryptionTypeGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("NetworkSecuritySettings").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    NetworkSecuritySettings(::Windows::Networking::Connectivity::NetworkSecuritySettings^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::NetworkSecuritySettings^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkSecuritySettings^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::NetworkSecuritySettings^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      NetworkSecuritySettings *wrapperInstance = new NetworkSecuritySettings(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkSecuritySettings^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::NetworkSecuritySettings^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::NetworkSecuritySettings^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapNetworkSecuritySettings(winRtInstance));
    }


  



    static void NetworkAuthenticationTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkSecuritySettings^>(info.This()))
      {
        return;
      }

      NetworkSecuritySettings *wrapper = NetworkSecuritySettings::Unwrap<NetworkSecuritySettings>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::NetworkAuthenticationType result = wrapper->_instance->NetworkAuthenticationType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NetworkEncryptionTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkSecuritySettings^>(info.This()))
      {
        return;
      }

      NetworkSecuritySettings *wrapper = NetworkSecuritySettings::Unwrap<NetworkSecuritySettings>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::NetworkEncryptionType result = wrapper->_instance->NetworkEncryptionType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::NetworkSecuritySettings^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapNetworkSecuritySettings(::Windows::Networking::Connectivity::NetworkSecuritySettings^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::NetworkSecuritySettings^ UnwrapNetworkSecuritySettings(Local<Value> value);
  };
  Persistent<FunctionTemplate> NetworkSecuritySettings::s_constructorTemplate;

  v8::Local<v8::Value> WrapNetworkSecuritySettings(::Windows::Networking::Connectivity::NetworkSecuritySettings^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(NetworkSecuritySettings::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::NetworkSecuritySettings^ UnwrapNetworkSecuritySettings(Local<Value> value)
  {
     return NetworkSecuritySettings::Unwrap<NetworkSecuritySettings>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitNetworkSecuritySettings(Local<Object> exports)
  {
    NetworkSecuritySettings::Init(exports);
  }

  class WlanConnectionProfileDetails : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("WlanConnectionProfileDetails").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getConnectedSsid", GetConnectedSsid);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("WlanConnectionProfileDetails").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    WlanConnectionProfileDetails(::Windows::Networking::Connectivity::WlanConnectionProfileDetails^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::WlanConnectionProfileDetails^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::WlanConnectionProfileDetails^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::WlanConnectionProfileDetails^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      WlanConnectionProfileDetails *wrapperInstance = new WlanConnectionProfileDetails(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::WlanConnectionProfileDetails^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::WlanConnectionProfileDetails^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::WlanConnectionProfileDetails^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapWlanConnectionProfileDetails(winRtInstance));
    }


  
    static void GetConnectedSsid(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::WlanConnectionProfileDetails^>(info.This()))
      {
        return;
      }

      WlanConnectionProfileDetails *wrapper = WlanConnectionProfileDetails::Unwrap<WlanConnectionProfileDetails>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetConnectedSsid();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





  private:
    ::Windows::Networking::Connectivity::WlanConnectionProfileDetails^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapWlanConnectionProfileDetails(::Windows::Networking::Connectivity::WlanConnectionProfileDetails^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::WlanConnectionProfileDetails^ UnwrapWlanConnectionProfileDetails(Local<Value> value);
  };
  Persistent<FunctionTemplate> WlanConnectionProfileDetails::s_constructorTemplate;

  v8::Local<v8::Value> WrapWlanConnectionProfileDetails(::Windows::Networking::Connectivity::WlanConnectionProfileDetails^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(WlanConnectionProfileDetails::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::WlanConnectionProfileDetails^ UnwrapWlanConnectionProfileDetails(Local<Value> value)
  {
     return WlanConnectionProfileDetails::Unwrap<WlanConnectionProfileDetails>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitWlanConnectionProfileDetails(Local<Object> exports)
  {
    WlanConnectionProfileDetails::Init(exports);
  }

  class NetworkUsage : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("NetworkUsage").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bytesReceived").ToLocalChecked(), BytesReceivedGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bytesSent").ToLocalChecked(), BytesSentGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("connectionDuration").ToLocalChecked(), ConnectionDurationGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("NetworkUsage").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    NetworkUsage(::Windows::Networking::Connectivity::NetworkUsage^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::NetworkUsage^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkUsage^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::NetworkUsage^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      NetworkUsage *wrapperInstance = new NetworkUsage(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkUsage^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::NetworkUsage^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::NetworkUsage^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapNetworkUsage(winRtInstance));
    }


  



    static void BytesReceivedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkUsage^>(info.This()))
      {
        return;
      }

      NetworkUsage *wrapper = NetworkUsage::Unwrap<NetworkUsage>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->BytesReceived;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BytesSentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkUsage^>(info.This()))
      {
        return;
      }

      NetworkUsage *wrapper = NetworkUsage::Unwrap<NetworkUsage>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->BytesSent;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ConnectionDurationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkUsage^>(info.This()))
      {
        return;
      }

      NetworkUsage *wrapper = NetworkUsage::Unwrap<NetworkUsage>(info.This());

      try 
      {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->ConnectionDuration;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::NetworkUsage^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapNetworkUsage(::Windows::Networking::Connectivity::NetworkUsage^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::NetworkUsage^ UnwrapNetworkUsage(Local<Value> value);
  };
  Persistent<FunctionTemplate> NetworkUsage::s_constructorTemplate;

  v8::Local<v8::Value> WrapNetworkUsage(::Windows::Networking::Connectivity::NetworkUsage^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(NetworkUsage::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::NetworkUsage^ UnwrapNetworkUsage(Local<Value> value)
  {
     return NetworkUsage::Unwrap<NetworkUsage>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitNetworkUsage(Local<Object> exports)
  {
    NetworkUsage::Init(exports);
  }

  class ConnectivityInterval : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ConnectivityInterval").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("connectionDuration").ToLocalChecked(), ConnectionDurationGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("startTime").ToLocalChecked(), StartTimeGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("ConnectivityInterval").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ConnectivityInterval(::Windows::Networking::Connectivity::ConnectivityInterval^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::ConnectivityInterval^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectivityInterval^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::ConnectivityInterval^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ConnectivityInterval *wrapperInstance = new ConnectivityInterval(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectivityInterval^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::ConnectivityInterval^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::ConnectivityInterval^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapConnectivityInterval(winRtInstance));
    }


  



    static void ConnectionDurationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectivityInterval^>(info.This()))
      {
        return;
      }

      ConnectivityInterval *wrapper = ConnectivityInterval::Unwrap<ConnectivityInterval>(info.This());

      try 
      {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->ConnectionDuration;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StartTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectivityInterval^>(info.This()))
      {
        return;
      }

      ConnectivityInterval *wrapper = ConnectivityInterval::Unwrap<ConnectivityInterval>(info.This());

      try 
      {
        ::Windows::Foundation::DateTime result = wrapper->_instance->StartTime;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::ConnectivityInterval^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapConnectivityInterval(::Windows::Networking::Connectivity::ConnectivityInterval^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::ConnectivityInterval^ UnwrapConnectivityInterval(Local<Value> value);
  };
  Persistent<FunctionTemplate> ConnectivityInterval::s_constructorTemplate;

  v8::Local<v8::Value> WrapConnectivityInterval(::Windows::Networking::Connectivity::ConnectivityInterval^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ConnectivityInterval::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::ConnectivityInterval^ UnwrapConnectivityInterval(Local<Value> value)
  {
     return ConnectivityInterval::Unwrap<ConnectivityInterval>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitConnectivityInterval(Local<Object> exports)
  {
    ConnectivityInterval::Init(exports);
  }

  class AttributedNetworkUsage : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("AttributedNetworkUsage").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributionId").ToLocalChecked(), AttributionIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributionName").ToLocalChecked(), AttributionNameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributionThumbnail").ToLocalChecked(), AttributionThumbnailGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bytesReceived").ToLocalChecked(), BytesReceivedGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bytesSent").ToLocalChecked(), BytesSentGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("AttributedNetworkUsage").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    AttributedNetworkUsage(::Windows::Networking::Connectivity::AttributedNetworkUsage^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::AttributedNetworkUsage^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::AttributedNetworkUsage^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::AttributedNetworkUsage^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      AttributedNetworkUsage *wrapperInstance = new AttributedNetworkUsage(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::AttributedNetworkUsage^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::AttributedNetworkUsage^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::AttributedNetworkUsage^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapAttributedNetworkUsage(winRtInstance));
    }


  



    static void AttributionIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::AttributedNetworkUsage^>(info.This()))
      {
        return;
      }

      AttributedNetworkUsage *wrapper = AttributedNetworkUsage::Unwrap<AttributedNetworkUsage>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->AttributionId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AttributionNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::AttributedNetworkUsage^>(info.This()))
      {
        return;
      }

      AttributedNetworkUsage *wrapper = AttributedNetworkUsage::Unwrap<AttributedNetworkUsage>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->AttributionName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AttributionThumbnailGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::AttributedNetworkUsage^>(info.This()))
      {
        return;
      }

      AttributedNetworkUsage *wrapper = AttributedNetworkUsage::Unwrap<AttributedNetworkUsage>(info.This());

      try 
      {
        ::Windows::Storage::Streams::IRandomAccessStreamReference^ result = wrapper->_instance->AttributionThumbnail;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IRandomAccessStreamReference", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BytesReceivedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::AttributedNetworkUsage^>(info.This()))
      {
        return;
      }

      AttributedNetworkUsage *wrapper = AttributedNetworkUsage::Unwrap<AttributedNetworkUsage>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->BytesReceived;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BytesSentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::AttributedNetworkUsage^>(info.This()))
      {
        return;
      }

      AttributedNetworkUsage *wrapper = AttributedNetworkUsage::Unwrap<AttributedNetworkUsage>(info.This());

      try 
      {
        unsigned __int64 result = wrapper->_instance->BytesSent;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::AttributedNetworkUsage^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapAttributedNetworkUsage(::Windows::Networking::Connectivity::AttributedNetworkUsage^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::AttributedNetworkUsage^ UnwrapAttributedNetworkUsage(Local<Value> value);
  };
  Persistent<FunctionTemplate> AttributedNetworkUsage::s_constructorTemplate;

  v8::Local<v8::Value> WrapAttributedNetworkUsage(::Windows::Networking::Connectivity::AttributedNetworkUsage^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(AttributedNetworkUsage::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::AttributedNetworkUsage^ UnwrapAttributedNetworkUsage(Local<Value> value)
  {
     return AttributedNetworkUsage::Unwrap<AttributedNetworkUsage>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitAttributedNetworkUsage(Local<Object> exports)
  {
    AttributedNetworkUsage::Init(exports);
  }

  class LanIdentifierData : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("LanIdentifierData").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("type").ToLocalChecked(), TypeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("value").ToLocalChecked(), ValueGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("LanIdentifierData").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    LanIdentifierData(::Windows::Networking::Connectivity::LanIdentifierData^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::LanIdentifierData^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::LanIdentifierData^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::LanIdentifierData^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      LanIdentifierData *wrapperInstance = new LanIdentifierData(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::LanIdentifierData^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::LanIdentifierData^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::LanIdentifierData^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapLanIdentifierData(winRtInstance));
    }


  



    static void TypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::LanIdentifierData^>(info.This()))
      {
        return;
      }

      LanIdentifierData *wrapper = LanIdentifierData::Unwrap<LanIdentifierData>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->Type;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::LanIdentifierData^>(info.This()))
      {
        return;
      }

      LanIdentifierData *wrapper = LanIdentifierData::Unwrap<LanIdentifierData>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<unsigned char>^ result = wrapper->_instance->Value;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<unsigned char>::CreateVectorViewWrapper(result, 
            [](unsigned char val) -> Local<Value> {
              return Nan::New<Integer>(val);
            },
            [](Local<Value> value) -> bool {
              return value->IsInt32();
            },
            [](Local<Value> value) -> unsigned char {
              return static_cast<unsigned char>(Nan::To<int32_t>(value).FromMaybe(0));
            }
          ));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::LanIdentifierData^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapLanIdentifierData(::Windows::Networking::Connectivity::LanIdentifierData^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::LanIdentifierData^ UnwrapLanIdentifierData(Local<Value> value);
  };
  Persistent<FunctionTemplate> LanIdentifierData::s_constructorTemplate;

  v8::Local<v8::Value> WrapLanIdentifierData(::Windows::Networking::Connectivity::LanIdentifierData^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(LanIdentifierData::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::LanIdentifierData^ UnwrapLanIdentifierData(Local<Value> value)
  {
     return LanIdentifierData::Unwrap<LanIdentifierData>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitLanIdentifierData(Local<Object> exports)
  {
    LanIdentifierData::Init(exports);
  }

  class ConnectionProfile : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ConnectionProfile").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "getNetworkConnectivityLevel", GetNetworkConnectivityLevel);
      Nan::SetPrototypeMethod(localRef, "getNetworkNames", GetNetworkNames);
      Nan::SetPrototypeMethod(localRef, "getConnectionCost", GetConnectionCost);
      Nan::SetPrototypeMethod(localRef, "getDataPlanStatus", GetDataPlanStatus);
      Nan::SetPrototypeMethod(localRef, "getLocalUsage", GetLocalUsage);
      Nan::SetPrototypeMethod(localRef, "getSignalBars", GetSignalBars);
      Nan::SetPrototypeMethod(localRef, "getDomainConnectivityLevel", GetDomainConnectivityLevel);
      
            
      Nan::SetPrototypeMethod(localRef, "getNetworkUsageAsync", GetNetworkUsageAsync);
      Nan::SetPrototypeMethod(localRef, "getConnectivityIntervalsAsync", GetConnectivityIntervalsAsync);
      Nan::SetPrototypeMethod(localRef, "getAttributedNetworkUsageAsync", GetAttributedNetworkUsageAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("networkAdapter").ToLocalChecked(), NetworkAdapterGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("networkSecuritySettings").ToLocalChecked(), NetworkSecuritySettingsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("profileName").ToLocalChecked(), ProfileNameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isWlanConnectionProfile").ToLocalChecked(), IsWlanConnectionProfileGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isWwanConnectionProfile").ToLocalChecked(), IsWwanConnectionProfileGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("serviceProviderGuid").ToLocalChecked(), ServiceProviderGuidGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("wlanConnectionProfileDetails").ToLocalChecked(), WlanConnectionProfileDetailsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("wwanConnectionProfileDetails").ToLocalChecked(), WwanConnectionProfileDetailsGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("ConnectionProfile").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ConnectionProfile(::Windows::Networking::Connectivity::ConnectionProfile^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::ConnectionProfile^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::ConnectionProfile^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ConnectionProfile *wrapperInstance = new ConnectionProfile(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::ConnectionProfile^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::ConnectionProfile^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapConnectionProfile(winRtInstance));
    }


    static void GetNetworkUsageAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Networking::Connectivity::NetworkUsage^>^>^ op;
    

      if (info.Length() == 5
        && info[0]->IsDate()
        && info[1]->IsDate()
        && info[2]->IsInt32()
        && IsNetworkUsageStatesJsObject(info[3]))
      {
        try
        {
          ::Windows::Foundation::DateTime arg0 = NodeRT::Utils::DateTimeFromJSDate(info[0]);
          ::Windows::Foundation::DateTime arg1 = NodeRT::Utils::DateTimeFromJSDate(info[1]);
          ::Windows::Networking::Connectivity::DataUsageGranularity arg2 = static_cast<::Windows::Networking::Connectivity::DataUsageGranularity>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          ::Windows::Networking::Connectivity::NetworkUsageStates arg3 = NetworkUsageStatesFromJsObject(info[3]);
          
          op = wrapper->_instance->GetNetworkUsageAsync(arg0,arg1,arg2,arg3);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Networking::Connectivity::NetworkUsage^>^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Networking::Connectivity::NetworkUsage^>::CreateVectorViewWrapper(result, 
            [](::Windows::Networking::Connectivity::NetworkUsage^ val) -> Local<Value> {
              return WrapNetworkUsage(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkUsage^>(value);
            },
            [](Local<Value> value) -> ::Windows::Networking::Connectivity::NetworkUsage^ {
              return UnwrapNetworkUsage(value);
            }
          );
            if (tryCatch.HasCaught())
            {
              error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
            }
            else 
            {
              error = Undefined();
            }
            if (arg1.IsEmpty()) arg1 = Undefined();
            Local<Value> args[] = {error, arg1};
			// TODO: this is ugly! Needed due to the possibility of expception occuring inside object convertors
			// can be fixed by wrapping the conversion code in a function and calling it on the fly
			// we must clear the try catch block here so the invoked inner method exception won't get swollen (issue #52) 
			tryCatch.~TryCatch();

		    
            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void GetConnectivityIntervalsAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Networking::Connectivity::ConnectivityInterval^>^>^ op;
    

      if (info.Length() == 4
        && info[0]->IsDate()
        && info[1]->IsDate()
        && IsNetworkUsageStatesJsObject(info[2]))
      {
        try
        {
          ::Windows::Foundation::DateTime arg0 = NodeRT::Utils::DateTimeFromJSDate(info[0]);
          ::Windows::Foundation::DateTime arg1 = NodeRT::Utils::DateTimeFromJSDate(info[1]);
          ::Windows::Networking::Connectivity::NetworkUsageStates arg2 = NetworkUsageStatesFromJsObject(info[2]);
          
          op = wrapper->_instance->GetConnectivityIntervalsAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Networking::Connectivity::ConnectivityInterval^>^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Networking::Connectivity::ConnectivityInterval^>::CreateVectorViewWrapper(result, 
            [](::Windows::Networking::Connectivity::ConnectivityInterval^ val) -> Local<Value> {
              return WrapConnectivityInterval(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectivityInterval^>(value);
            },
            [](Local<Value> value) -> ::Windows::Networking::Connectivity::ConnectivityInterval^ {
              return UnwrapConnectivityInterval(value);
            }
          );
            if (tryCatch.HasCaught())
            {
              error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
            }
            else 
            {
              error = Undefined();
            }
            if (arg1.IsEmpty()) arg1 = Undefined();
            Local<Value> args[] = {error, arg1};
			// TODO: this is ugly! Needed due to the possibility of expception occuring inside object convertors
			// can be fixed by wrapping the conversion code in a function and calling it on the fly
			// we must clear the try catch block here so the invoked inner method exception won't get swollen (issue #52) 
			tryCatch.~TryCatch();

		    
            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void GetAttributedNetworkUsageAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Networking::Connectivity::AttributedNetworkUsage^>^>^ op;
    

      if (info.Length() == 4
        && info[0]->IsDate()
        && info[1]->IsDate()
        && IsNetworkUsageStatesJsObject(info[2]))
      {
        try
        {
          ::Windows::Foundation::DateTime arg0 = NodeRT::Utils::DateTimeFromJSDate(info[0]);
          ::Windows::Foundation::DateTime arg1 = NodeRT::Utils::DateTimeFromJSDate(info[1]);
          ::Windows::Networking::Connectivity::NetworkUsageStates arg2 = NetworkUsageStatesFromJsObject(info[2]);
          
          op = wrapper->_instance->GetAttributedNetworkUsageAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Networking::Connectivity::AttributedNetworkUsage^>^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Networking::Connectivity::AttributedNetworkUsage^>::CreateVectorViewWrapper(result, 
            [](::Windows::Networking::Connectivity::AttributedNetworkUsage^ val) -> Local<Value> {
              return WrapAttributedNetworkUsage(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::AttributedNetworkUsage^>(value);
            },
            [](Local<Value> value) -> ::Windows::Networking::Connectivity::AttributedNetworkUsage^ {
              return UnwrapAttributedNetworkUsage(value);
            }
          );
            if (tryCatch.HasCaught())
            {
              error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
            }
            else 
            {
              error = Undefined();
            }
            if (arg1.IsEmpty()) arg1 = Undefined();
            Local<Value> args[] = {error, arg1};
			// TODO: this is ugly! Needed due to the possibility of expception occuring inside object convertors
			// can be fixed by wrapping the conversion code in a function and calling it on the fly
			// we must clear the try catch block here so the invoked inner method exception won't get swollen (issue #52) 
			tryCatch.~TryCatch();

		    
            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  
    static void GetNetworkConnectivityLevel(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Networking::Connectivity::NetworkConnectivityLevel result;
          result = wrapper->_instance->GetNetworkConnectivityLevel();
          info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetNetworkNames(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Platform::String^>^ result;
          result = wrapper->_instance->GetNetworkNames();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Platform::String^>::CreateVectorViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));
            }
          ));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetConnectionCost(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Networking::Connectivity::ConnectionCost^ result;
          result = wrapper->_instance->GetConnectionCost();
          info.GetReturnValue().Set(WrapConnectionCost(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetDataPlanStatus(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Networking::Connectivity::DataPlanStatus^ result;
          result = wrapper->_instance->GetDataPlanStatus();
          info.GetReturnValue().Set(WrapDataPlanStatus(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetLocalUsage(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      if (info.Length() == 2
        && info[0]->IsDate()
        && info[1]->IsDate())
      {
        try
        {
          ::Windows::Foundation::DateTime arg0 = NodeRT::Utils::DateTimeFromJSDate(info[0]);
          ::Windows::Foundation::DateTime arg1 = NodeRT::Utils::DateTimeFromJSDate(info[1]);
          
          ::Windows::Networking::Connectivity::DataUsage^ result;
          result = wrapper->_instance->GetLocalUsage(arg0, arg1);
          info.GetReturnValue().Set(WrapDataUsage(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsDate()
        && info[1]->IsDate()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::DateTime arg0 = NodeRT::Utils::DateTimeFromJSDate(info[0]);
          ::Windows::Foundation::DateTime arg1 = NodeRT::Utils::DateTimeFromJSDate(info[1]);
          ::Windows::Networking::Connectivity::RoamingStates arg2 = static_cast<::Windows::Networking::Connectivity::RoamingStates>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          ::Windows::Networking::Connectivity::DataUsage^ result;
          result = wrapper->_instance->GetLocalUsage(arg0, arg1, arg2);
          info.GetReturnValue().Set(WrapDataUsage(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetSignalBars(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::IBox<unsigned char>^ result;
          result = wrapper->_instance->GetSignalBars();
          info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetDomainConnectivityLevel(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Networking::Connectivity::DomainConnectivityLevel result;
          result = wrapper->_instance->GetDomainConnectivityLevel();
          info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void NetworkAdapterGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::NetworkAdapter^ result = wrapper->_instance->NetworkAdapter;
        info.GetReturnValue().Set(WrapNetworkAdapter(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NetworkSecuritySettingsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::NetworkSecuritySettings^ result = wrapper->_instance->NetworkSecuritySettings;
        info.GetReturnValue().Set(WrapNetworkSecuritySettings(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ProfileNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->ProfileName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsWlanConnectionProfileGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsWlanConnectionProfile;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsWwanConnectionProfileGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsWwanConnectionProfile;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ServiceProviderGuidGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      try 
      {
        ::Platform::IBox<::Platform::Guid>^ result = wrapper->_instance->ServiceProviderGuid;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(NodeRT::Utils::GuidToJs(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void WlanConnectionProfileDetailsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::WlanConnectionProfileDetails^ result = wrapper->_instance->WlanConnectionProfileDetails;
        info.GetReturnValue().Set(WrapWlanConnectionProfileDetails(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void WwanConnectionProfileDetailsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info.This()))
      {
        return;
      }

      ConnectionProfile *wrapper = ConnectionProfile::Unwrap<ConnectionProfile>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::WwanConnectionProfileDetails^ result = wrapper->_instance->WwanConnectionProfileDetails;
        info.GetReturnValue().Set(WrapWwanConnectionProfileDetails(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::ConnectionProfile^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapConnectionProfile(::Windows::Networking::Connectivity::ConnectionProfile^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::ConnectionProfile^ UnwrapConnectionProfile(Local<Value> value);
  };
  Persistent<FunctionTemplate> ConnectionProfile::s_constructorTemplate;

  v8::Local<v8::Value> WrapConnectionProfile(::Windows::Networking::Connectivity::ConnectionProfile^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ConnectionProfile::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::ConnectionProfile^ UnwrapConnectionProfile(Local<Value> value)
  {
     return ConnectionProfile::Unwrap<ConnectionProfile>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitConnectionProfile(Local<Object> exports)
  {
    ConnectionProfile::Init(exports);
  }

  class LanIdentifier : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("LanIdentifier").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("infrastructureId").ToLocalChecked(), InfrastructureIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("networkAdapterId").ToLocalChecked(), NetworkAdapterIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("portId").ToLocalChecked(), PortIdGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("LanIdentifier").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    LanIdentifier(::Windows::Networking::Connectivity::LanIdentifier^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::LanIdentifier^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::LanIdentifier^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::LanIdentifier^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      LanIdentifier *wrapperInstance = new LanIdentifier(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::LanIdentifier^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::LanIdentifier^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::LanIdentifier^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapLanIdentifier(winRtInstance));
    }


  



    static void InfrastructureIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::LanIdentifier^>(info.This()))
      {
        return;
      }

      LanIdentifier *wrapper = LanIdentifier::Unwrap<LanIdentifier>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::LanIdentifierData^ result = wrapper->_instance->InfrastructureId;
        info.GetReturnValue().Set(WrapLanIdentifierData(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NetworkAdapterIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::LanIdentifier^>(info.This()))
      {
        return;
      }

      LanIdentifier *wrapper = LanIdentifier::Unwrap<LanIdentifier>(info.This());

      try 
      {
        ::Platform::Guid result = wrapper->_instance->NetworkAdapterId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PortIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::LanIdentifier^>(info.This()))
      {
        return;
      }

      LanIdentifier *wrapper = LanIdentifier::Unwrap<LanIdentifier>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::LanIdentifierData^ result = wrapper->_instance->PortId;
        info.GetReturnValue().Set(WrapLanIdentifierData(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::LanIdentifier^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapLanIdentifier(::Windows::Networking::Connectivity::LanIdentifier^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::LanIdentifier^ UnwrapLanIdentifier(Local<Value> value);
  };
  Persistent<FunctionTemplate> LanIdentifier::s_constructorTemplate;

  v8::Local<v8::Value> WrapLanIdentifier(::Windows::Networking::Connectivity::LanIdentifier^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(LanIdentifier::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::LanIdentifier^ UnwrapLanIdentifier(Local<Value> value)
  {
     return LanIdentifier::Unwrap<LanIdentifier>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitLanIdentifier(Local<Object> exports)
  {
    LanIdentifier::Init(exports);
  }

  class ProxyConfiguration : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ProxyConfiguration").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canConnectDirectly").ToLocalChecked(), CanConnectDirectlyGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("proxyUris").ToLocalChecked(), ProxyUrisGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("ProxyConfiguration").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ProxyConfiguration(::Windows::Networking::Connectivity::ProxyConfiguration^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::ProxyConfiguration^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ProxyConfiguration^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::ProxyConfiguration^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ProxyConfiguration *wrapperInstance = new ProxyConfiguration(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ProxyConfiguration^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::ProxyConfiguration^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::ProxyConfiguration^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapProxyConfiguration(winRtInstance));
    }


  



    static void CanConnectDirectlyGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ProxyConfiguration^>(info.This()))
      {
        return;
      }

      ProxyConfiguration *wrapper = ProxyConfiguration::Unwrap<ProxyConfiguration>(info.This());

      try 
      {
        bool result = wrapper->_instance->CanConnectDirectly;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ProxyUrisGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ProxyConfiguration^>(info.This()))
      {
        return;
      }

      ProxyConfiguration *wrapper = ProxyConfiguration::Unwrap<ProxyConfiguration>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Foundation::Uri^>^ result = wrapper->_instance->ProxyUris;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Foundation::Uri^>::CreateVectorViewWrapper(result, 
            [](::Windows::Foundation::Uri^ val) -> Local<Value> {
              return NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value);
            },
            [](Local<Value> value) -> ::Windows::Foundation::Uri^ {
              return dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));
            }
          ));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::ProxyConfiguration^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapProxyConfiguration(::Windows::Networking::Connectivity::ProxyConfiguration^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::ProxyConfiguration^ UnwrapProxyConfiguration(Local<Value> value);
  };
  Persistent<FunctionTemplate> ProxyConfiguration::s_constructorTemplate;

  v8::Local<v8::Value> WrapProxyConfiguration(::Windows::Networking::Connectivity::ProxyConfiguration^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ProxyConfiguration::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::ProxyConfiguration^ UnwrapProxyConfiguration(Local<Value> value)
  {
     return ProxyConfiguration::Unwrap<ProxyConfiguration>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitProxyConfiguration(Local<Object> exports)
  {
    ProxyConfiguration::Init(exports);
  }

  class ConnectionProfileFilter : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ConnectionProfileFilter").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("serviceProviderGuid").ToLocalChecked(), ServiceProviderGuidGetter, ServiceProviderGuidSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("networkCostType").ToLocalChecked(), NetworkCostTypeGetter, NetworkCostTypeSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isWwanConnectionProfile").ToLocalChecked(), IsWwanConnectionProfileGetter, IsWwanConnectionProfileSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isWlanConnectionProfile").ToLocalChecked(), IsWlanConnectionProfileGetter, IsWlanConnectionProfileSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isConnected").ToLocalChecked(), IsConnectedGetter, IsConnectedSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isRoaming").ToLocalChecked(), IsRoamingGetter, IsRoamingSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isOverDataLimit").ToLocalChecked(), IsOverDataLimitGetter, IsOverDataLimitSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isBackgroundDataUsageRestricted").ToLocalChecked(), IsBackgroundDataUsageRestrictedGetter, IsBackgroundDataUsageRestrictedSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("rawData").ToLocalChecked(), RawDataGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("ConnectionProfileFilter").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ConnectionProfileFilter(::Windows::Networking::Connectivity::ConnectionProfileFilter^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::ConnectionProfileFilter^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::ConnectionProfileFilter^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try
        {
          winRtInstance = ref new ::Windows::Networking::Connectivity::ConnectionProfileFilter();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ConnectionProfileFilter *wrapperInstance = new ConnectionProfileFilter(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::ConnectionProfileFilter^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::ConnectionProfileFilter^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapConnectionProfileFilter(winRtInstance));
    }


  



    static void ServiceProviderGuidGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        ::Platform::IBox<::Platform::Guid>^ result = wrapper->_instance->ServiceProviderGuid;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(NodeRT::Utils::GuidToJs(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ServiceProviderGuidSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsGuid(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        
        ::Platform::IBox<::Platform::Guid>^ winRtValue = ref new ::Platform::Box<::Platform::Guid>(NodeRT::Utils::GuidFromJs(value));

        wrapper->_instance->ServiceProviderGuid = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void NetworkCostTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::NetworkCostType result = wrapper->_instance->NetworkCostType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NetworkCostTypeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        
        ::Windows::Networking::Connectivity::NetworkCostType winRtValue = static_cast<::Windows::Networking::Connectivity::NetworkCostType>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->NetworkCostType = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void IsWwanConnectionProfileGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsWwanConnectionProfile;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsWwanConnectionProfileSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        
        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsWwanConnectionProfile = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void IsWlanConnectionProfileGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsWlanConnectionProfile;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsWlanConnectionProfileSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        
        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsWlanConnectionProfile = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void IsConnectedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsConnected;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsConnectedSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        
        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsConnected = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void IsRoamingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        ::Platform::IBox<bool>^ result = wrapper->_instance->IsRoaming;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Boolean>(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsRoamingSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        
        ::Platform::IBox<bool>^ winRtValue = ref new ::Platform::Box<bool>(Nan::To<bool>(value).FromMaybe(false));

        wrapper->_instance->IsRoaming = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void IsOverDataLimitGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        ::Platform::IBox<bool>^ result = wrapper->_instance->IsOverDataLimit;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Boolean>(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsOverDataLimitSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        
        ::Platform::IBox<bool>^ winRtValue = ref new ::Platform::Box<bool>(Nan::To<bool>(value).FromMaybe(false));

        wrapper->_instance->IsOverDataLimit = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void IsBackgroundDataUsageRestrictedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        ::Platform::IBox<bool>^ result = wrapper->_instance->IsBackgroundDataUsageRestricted;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Boolean>(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsBackgroundDataUsageRestrictedSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        
        ::Platform::IBox<bool>^ winRtValue = ref new ::Platform::Box<bool>(Nan::To<bool>(value).FromMaybe(false));

        wrapper->_instance->IsBackgroundDataUsageRestricted = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void RawDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info.This()))
      {
        return;
      }

      ConnectionProfileFilter *wrapper = ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(info.This());

      try 
      {
        ::Windows::Storage::Streams::IBuffer^ result = wrapper->_instance->RawData;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::ConnectionProfileFilter^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapConnectionProfileFilter(::Windows::Networking::Connectivity::ConnectionProfileFilter^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::ConnectionProfileFilter^ UnwrapConnectionProfileFilter(Local<Value> value);
  };
  Persistent<FunctionTemplate> ConnectionProfileFilter::s_constructorTemplate;

  v8::Local<v8::Value> WrapConnectionProfileFilter(::Windows::Networking::Connectivity::ConnectionProfileFilter^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ConnectionProfileFilter::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::ConnectionProfileFilter^ UnwrapConnectionProfileFilter(Local<Value> value)
  {
     return ConnectionProfileFilter::Unwrap<ConnectionProfileFilter>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitConnectionProfileFilter(Local<Object> exports)
  {
    ConnectionProfileFilter::Init(exports);
  }

  class NetworkItem : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("NetworkItem").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getNetworkTypes", GetNetworkTypes);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("networkId").ToLocalChecked(), NetworkIdGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("NetworkItem").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    NetworkItem(::Windows::Networking::Connectivity::NetworkItem^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::NetworkItem^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkItem^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::NetworkItem^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      NetworkItem *wrapperInstance = new NetworkItem(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkItem^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::NetworkItem^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::NetworkItem^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapNetworkItem(winRtInstance));
    }


  
    static void GetNetworkTypes(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkItem^>(info.This()))
      {
        return;
      }

      NetworkItem *wrapper = NetworkItem::Unwrap<NetworkItem>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Networking::Connectivity::NetworkTypes result;
          result = wrapper->_instance->GetNetworkTypes();
          info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void NetworkIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkItem^>(info.This()))
      {
        return;
      }

      NetworkItem *wrapper = NetworkItem::Unwrap<NetworkItem>(info.This());

      try 
      {
        ::Platform::Guid result = wrapper->_instance->NetworkId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::NetworkItem^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapNetworkItem(::Windows::Networking::Connectivity::NetworkItem^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::NetworkItem^ UnwrapNetworkItem(Local<Value> value);
  };
  Persistent<FunctionTemplate> NetworkItem::s_constructorTemplate;

  v8::Local<v8::Value> WrapNetworkItem(::Windows::Networking::Connectivity::NetworkItem^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(NetworkItem::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::NetworkItem^ UnwrapNetworkItem(Local<Value> value)
  {
     return NetworkItem::Unwrap<NetworkItem>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitNetworkItem(Local<Object> exports)
  {
    NetworkItem::Init(exports);
  }

  class RoutePolicy : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("RoutePolicy").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("connectionProfile").ToLocalChecked(), ConnectionProfileGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hostName").ToLocalChecked(), HostNameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hostNameType").ToLocalChecked(), HostNameTypeGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("RoutePolicy").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    RoutePolicy(::Windows::Networking::Connectivity::RoutePolicy^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::RoutePolicy^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::RoutePolicy^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::RoutePolicy^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::HostName^>(info[1])
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Networking::Connectivity::ConnectionProfile^ arg0 = UnwrapConnectionProfile(info[0]);
          ::Windows::Networking::HostName^ arg1 = dynamic_cast<::Windows::Networking::HostName^>(NodeRT::Utils::GetObjectInstance(info[1]));
          ::Windows::Networking::DomainNameType arg2 = static_cast<::Windows::Networking::DomainNameType>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Networking::Connectivity::RoutePolicy(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      RoutePolicy *wrapperInstance = new RoutePolicy(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::RoutePolicy^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::RoutePolicy^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::RoutePolicy^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapRoutePolicy(winRtInstance));
    }


  



    static void ConnectionProfileGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::RoutePolicy^>(info.This()))
      {
        return;
      }

      RoutePolicy *wrapper = RoutePolicy::Unwrap<RoutePolicy>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::ConnectionProfile^ result = wrapper->_instance->ConnectionProfile;
        info.GetReturnValue().Set(WrapConnectionProfile(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HostNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::RoutePolicy^>(info.This()))
      {
        return;
      }

      RoutePolicy *wrapper = RoutePolicy::Unwrap<RoutePolicy>(info.This());

      try 
      {
        ::Windows::Networking::HostName^ result = wrapper->_instance->HostName;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Networking", "HostName", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HostNameTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::RoutePolicy^>(info.This()))
      {
        return;
      }

      RoutePolicy *wrapper = RoutePolicy::Unwrap<RoutePolicy>(info.This());

      try 
      {
        ::Windows::Networking::DomainNameType result = wrapper->_instance->HostNameType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::RoutePolicy^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapRoutePolicy(::Windows::Networking::Connectivity::RoutePolicy^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::RoutePolicy^ UnwrapRoutePolicy(Local<Value> value);
  };
  Persistent<FunctionTemplate> RoutePolicy::s_constructorTemplate;

  v8::Local<v8::Value> WrapRoutePolicy(::Windows::Networking::Connectivity::RoutePolicy^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(RoutePolicy::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::RoutePolicy^ UnwrapRoutePolicy(Local<Value> value)
  {
     return RoutePolicy::Unwrap<RoutePolicy>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitRoutePolicy(Local<Object> exports)
  {
    RoutePolicy::Init(exports);
  }

  class CellularApnContext : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("CellularApnContext").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("userName").ToLocalChecked(), UserNameGetter, UserNameSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("providerId").ToLocalChecked(), ProviderIdGetter, ProviderIdSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("password").ToLocalChecked(), PasswordGetter, PasswordSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isCompressionEnabled").ToLocalChecked(), IsCompressionEnabledGetter, IsCompressionEnabledSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("authenticationType").ToLocalChecked(), AuthenticationTypeGetter, AuthenticationTypeSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("accessPointName").ToLocalChecked(), AccessPointNameGetter, AccessPointNameSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("CellularApnContext").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    CellularApnContext(::Windows::Networking::Connectivity::CellularApnContext^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::CellularApnContext^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::CellularApnContext^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::CellularApnContext^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try
        {
          winRtInstance = ref new ::Windows::Networking::Connectivity::CellularApnContext();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      CellularApnContext *wrapperInstance = new CellularApnContext(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::CellularApnContext^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::CellularApnContext^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::CellularApnContext^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapCellularApnContext(winRtInstance));
    }


  



    static void UserNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::CellularApnContext^>(info.This()))
      {
        return;
      }

      CellularApnContext *wrapper = CellularApnContext::Unwrap<CellularApnContext>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->UserName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UserNameSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::CellularApnContext^>(info.This()))
      {
        return;
      }

      CellularApnContext *wrapper = CellularApnContext::Unwrap<CellularApnContext>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->UserName = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ProviderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::CellularApnContext^>(info.This()))
      {
        return;
      }

      CellularApnContext *wrapper = CellularApnContext::Unwrap<CellularApnContext>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->ProviderId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ProviderIdSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::CellularApnContext^>(info.This()))
      {
        return;
      }

      CellularApnContext *wrapper = CellularApnContext::Unwrap<CellularApnContext>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->ProviderId = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void PasswordGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::CellularApnContext^>(info.This()))
      {
        return;
      }

      CellularApnContext *wrapper = CellularApnContext::Unwrap<CellularApnContext>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Password;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PasswordSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::CellularApnContext^>(info.This()))
      {
        return;
      }

      CellularApnContext *wrapper = CellularApnContext::Unwrap<CellularApnContext>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Password = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void IsCompressionEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::CellularApnContext^>(info.This()))
      {
        return;
      }

      CellularApnContext *wrapper = CellularApnContext::Unwrap<CellularApnContext>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsCompressionEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsCompressionEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::CellularApnContext^>(info.This()))
      {
        return;
      }

      CellularApnContext *wrapper = CellularApnContext::Unwrap<CellularApnContext>(info.This());

      try 
      {
        
        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsCompressionEnabled = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void AuthenticationTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::CellularApnContext^>(info.This()))
      {
        return;
      }

      CellularApnContext *wrapper = CellularApnContext::Unwrap<CellularApnContext>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::CellularApnAuthenticationType result = wrapper->_instance->AuthenticationType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AuthenticationTypeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::CellularApnContext^>(info.This()))
      {
        return;
      }

      CellularApnContext *wrapper = CellularApnContext::Unwrap<CellularApnContext>(info.This());

      try 
      {
        
        ::Windows::Networking::Connectivity::CellularApnAuthenticationType winRtValue = static_cast<::Windows::Networking::Connectivity::CellularApnAuthenticationType>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->AuthenticationType = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void AccessPointNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::CellularApnContext^>(info.This()))
      {
        return;
      }

      CellularApnContext *wrapper = CellularApnContext::Unwrap<CellularApnContext>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->AccessPointName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AccessPointNameSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::CellularApnContext^>(info.This()))
      {
        return;
      }

      CellularApnContext *wrapper = CellularApnContext::Unwrap<CellularApnContext>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->AccessPointName = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::CellularApnContext^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapCellularApnContext(::Windows::Networking::Connectivity::CellularApnContext^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::CellularApnContext^ UnwrapCellularApnContext(Local<Value> value);
  };
  Persistent<FunctionTemplate> CellularApnContext::s_constructorTemplate;

  v8::Local<v8::Value> WrapCellularApnContext(::Windows::Networking::Connectivity::CellularApnContext^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(CellularApnContext::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::CellularApnContext^ UnwrapCellularApnContext(Local<Value> value)
  {
     return CellularApnContext::Unwrap<CellularApnContext>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitCellularApnContext(Local<Object> exports)
  {
    CellularApnContext::Init(exports);
  }

  class ConnectionSession : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ConnectionSession").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "close", Close);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("connectionProfile").ToLocalChecked(), ConnectionProfileGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("ConnectionSession").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ConnectionSession(::Windows::Networking::Connectivity::ConnectionSession^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::ConnectionSession^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionSession^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::ConnectionSession^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ConnectionSession *wrapperInstance = new ConnectionSession(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionSession^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::ConnectionSession^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::ConnectionSession^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapConnectionSession(winRtInstance));
    }


  
    static void Close(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionSession^>(info.This()))
      {
	    return;
      }

      ConnectionSession *wrapper = ConnectionSession::Unwrap<ConnectionSession>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
		  return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
		  return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
		return;
      }
    }




    static void ConnectionProfileGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionSession^>(info.This()))
      {
        return;
      }

      ConnectionSession *wrapper = ConnectionSession::Unwrap<ConnectionSession>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::ConnectionProfile^ result = wrapper->_instance->ConnectionProfile;
        info.GetReturnValue().Set(WrapConnectionProfile(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::ConnectionSession^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapConnectionSession(::Windows::Networking::Connectivity::ConnectionSession^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::ConnectionSession^ UnwrapConnectionSession(Local<Value> value);
  };
  Persistent<FunctionTemplate> ConnectionSession::s_constructorTemplate;

  v8::Local<v8::Value> WrapConnectionSession(::Windows::Networking::Connectivity::ConnectionSession^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ConnectionSession::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::ConnectionSession^ UnwrapConnectionSession(Local<Value> value)
  {
     return ConnectionSession::Unwrap<ConnectionSession>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitConnectionSession(Local<Object> exports)
  {
    ConnectionSession::Init(exports);
  }

  class NetworkInformation : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("NetworkInformation").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "getConnectionProfiles", GetConnectionProfiles);
      Nan::SetMethod(constructor, "getInternetConnectionProfile", GetInternetConnectionProfile);
      Nan::SetMethod(constructor, "getLanIdentifiers", GetLanIdentifiers);
      Nan::SetMethod(constructor, "getHostNames", GetHostNames);
      Nan::SetMethod(constructor, "getSortedEndpointPairs", GetSortedEndpointPairs);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(FindConnectionProfilesAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("findConnectionProfilesAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(GetProxyConfigurationAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("getProxyConfigurationAsync").ToLocalChecked(), func);
      
      Local<Function> addListenerFunc = Nan::GetFunction(Nan::New<FunctionTemplate>(AddListener)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("addListener").ToLocalChecked(), addListenerFunc);
      Nan::Set(constructor, Nan::New<String>("on").ToLocalChecked(), addListenerFunc);
      Local<Function> removeListenerFunc = Nan::GetFunction(Nan::New<FunctionTemplate>(RemoveListener)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("removeListener").ToLocalChecked(), removeListenerFunc);
      Nan::Set(constructor, Nan::New<String>("off").ToLocalChecked(), removeListenerFunc);

      Nan::Set(exports, Nan::New<String>("NetworkInformation").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    NetworkInformation(::Windows::Networking::Connectivity::NetworkInformation^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::NetworkInformation^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkInformation^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::NetworkInformation^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      NetworkInformation *wrapperInstance = new NetworkInformation(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkInformation^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::NetworkInformation^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::NetworkInformation^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapNetworkInformation(winRtInstance));
    }


  

    static void FindConnectionProfilesAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Networking::Connectivity::ConnectionProfile^>^>^ op;
      

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfileFilter^>(info[0]))
      {
        try
        {
          ::Windows::Networking::Connectivity::ConnectionProfileFilter^ arg0 = UnwrapConnectionProfileFilter(info[0]);
          
          op = ::Windows::Networking::Connectivity::NetworkInformation::FindConnectionProfilesAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Networking::Connectivity::ConnectionProfile^>^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Networking::Connectivity::ConnectionProfile^>::CreateVectorViewWrapper(result, 
            [](::Windows::Networking::Connectivity::ConnectionProfile^ val) -> Local<Value> {
              return WrapConnectionProfile(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(value);
            },
            [](Local<Value> value) -> ::Windows::Networking::Connectivity::ConnectionProfile^ {
              return UnwrapConnectionProfile(value);
            }
          );
            if (tryCatch.HasCaught())
            {
              error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
            }
            else 
            {
              error = Undefined();
            }
            if (arg1.IsEmpty()) arg1 = Undefined();
            Local<Value> args[] = {error, arg1};
			// TODO: this is ugly! Needed due to the possibility of expception occuring inside object convertors
			// can be fixed by wrapping the conversion code in a function and calling it on the fly
			// we must clear the try catch block here so the invoked inner method exception won't get swollen (issue #52) 
			tryCatch.~TryCatch();

	  	    
            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
          
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void GetProxyConfigurationAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Networking::Connectivity::ProxyConfiguration^>^ op;
      

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[0]))
      {
        try
        {
          ::Windows::Foundation::Uri^ arg0 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = ::Windows::Networking::Connectivity::NetworkInformation::GetProxyConfigurationAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Networking::Connectivity::ProxyConfiguration^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = WrapProxyConfiguration(result);
            if (tryCatch.HasCaught())
            {
              error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
            }
            else 
            {
              error = Undefined();
            }
            if (arg1.IsEmpty()) arg1 = Undefined();
            Local<Value> args[] = {error, arg1};
			// TODO: this is ugly! Needed due to the possibility of expception occuring inside object convertors
			// can be fixed by wrapping the conversion code in a function and calling it on the fly
			// we must clear the try catch block here so the invoked inner method exception won't get swollen (issue #52) 
			tryCatch.~TryCatch();

	  	    
            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
          
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }

    static void GetConnectionProfiles(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::Networking::Connectivity::ConnectionProfile^>^ result;
          result = ::Windows::Networking::Connectivity::NetworkInformation::GetConnectionProfiles();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Networking::Connectivity::ConnectionProfile^>::CreateVectorViewWrapper(result, 
            [](::Windows::Networking::Connectivity::ConnectionProfile^ val) -> Local<Value> {
              return WrapConnectionProfile(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectionProfile^>(value);
            },
            [](Local<Value> value) -> ::Windows::Networking::Connectivity::ConnectionProfile^ {
              return UnwrapConnectionProfile(value);
            }
          ));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetInternetConnectionProfile(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Networking::Connectivity::ConnectionProfile^ result;
          result = ::Windows::Networking::Connectivity::NetworkInformation::GetInternetConnectionProfile();
          info.GetReturnValue().Set(WrapConnectionProfile(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetLanIdentifiers(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::Networking::Connectivity::LanIdentifier^>^ result;
          result = ::Windows::Networking::Connectivity::NetworkInformation::GetLanIdentifiers();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Networking::Connectivity::LanIdentifier^>::CreateVectorViewWrapper(result, 
            [](::Windows::Networking::Connectivity::LanIdentifier^ val) -> Local<Value> {
              return WrapLanIdentifier(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::LanIdentifier^>(value);
            },
            [](Local<Value> value) -> ::Windows::Networking::Connectivity::LanIdentifier^ {
              return UnwrapLanIdentifier(value);
            }
          ));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetHostNames(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::Networking::HostName^>^ result;
          result = ::Windows::Networking::Connectivity::NetworkInformation::GetHostNames();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Networking::HostName^>::CreateVectorViewWrapper(result, 
            [](::Windows::Networking::HostName^ val) -> Local<Value> {
              return NodeRT::Utils::CreateExternalWinRTObject("Windows.Networking", "HostName", val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::HostName^>(value);
            },
            [](Local<Value> value) -> ::Windows::Networking::HostName^ {
              return dynamic_cast<::Windows::Networking::HostName^>(NodeRT::Utils::GetObjectInstance(value));
            }
          ));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetSortedEndpointPairs(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Networking::EndpointPair^>^>(info[0]) || info[0]->IsArray())
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Networking::EndpointPair^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Networking::EndpointPair^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::Networking::EndpointPair^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::EndpointPair^>(value);
                 },
                 [](Local<Value> value) -> ::Windows::Networking::EndpointPair^ {
                   return dynamic_cast<::Windows::Networking::EndpointPair^>(NodeRT::Utils::GetObjectInstance(value));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Networking::EndpointPair^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          ::Windows::Networking::HostNameSortOptions arg1 = static_cast<::Windows::Networking::HostNameSortOptions>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          ::Windows::Foundation::Collections::IVectorView<::Windows::Networking::EndpointPair^>^ result;
          result = ::Windows::Networking::Connectivity::NetworkInformation::GetSortedEndpointPairs(arg0, arg1);
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Networking::EndpointPair^>::CreateVectorViewWrapper(result, 
            [](::Windows::Networking::EndpointPair^ val) -> Local<Value> {
              return NodeRT::Utils::CreateExternalWinRTObject("Windows.Networking", "EndpointPair", val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::EndpointPair^>(value);
            },
            [](Local<Value> value) -> ::Windows::Networking::EndpointPair^ {
              return dynamic_cast<::Windows::Networking::EndpointPair^>(NodeRT::Utils::GetObjectInstance(value));
            }
          ));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
		return;
      }

      String::Value eventName(info[0]);
      auto str = *eventName;
      
      Local<Function> callback = info[1].As<Function>();
      
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"networkStatusChanged", str))
      {
      
        try
        {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr, 
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = ::Windows::Networking::Connectivity::NetworkInformation::NetworkStatusChanged::add(
            ref new ::Windows::Networking::Connectivity::NetworkStatusChangedEventHandler(
            [callbackObjPtr](::Platform::Object^ arg0) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0]() {
           	    HandleScope scope;
                TryCatch tryCatch;
              
                Local<Value> error;

                Local<Value> wrappedArg0 = CreateOpaqueWrapper(arg0);

                if (tryCatch.HasCaught())
                {
                  error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
                }
                else 
                {
                  error = Undefined();
                }

				// TODO: this is ugly! Needed due to the possibility of expception occuring inside object convertors
				// can be fixed by wrapping the conversion code in a function and calling it on the fly
				// we must clear the try catch block here so the invoked inner method exception won't get swollen (issue #52) 
				tryCatch.~TryCatch();


                if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();

                Local<Value> args[] = { wrappedArg0 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else 
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
		return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false))
      {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      }
      else
      {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(info[0]);
      auto str = *eventName;

      if ((NodeRT::Utils::CaseInsenstiveEquals(L"networkStatusChanged", str)))
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
                
      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false))
      {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false))
      {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());
            
      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;
        
      try 
      {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"networkStatusChanged", str))
        {
          ::Windows::Networking::Connectivity::NetworkInformation::NetworkStatusChanged::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Networking::Connectivity::NetworkInformation^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapNetworkInformation(::Windows::Networking::Connectivity::NetworkInformation^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::NetworkInformation^ UnwrapNetworkInformation(Local<Value> value);
  };
  Persistent<FunctionTemplate> NetworkInformation::s_constructorTemplate;

  v8::Local<v8::Value> WrapNetworkInformation(::Windows::Networking::Connectivity::NetworkInformation^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(NetworkInformation::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::NetworkInformation^ UnwrapNetworkInformation(Local<Value> value)
  {
     return NetworkInformation::Unwrap<NetworkInformation>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitNetworkInformation(Local<Object> exports)
  {
    NetworkInformation::Init(exports);
  }

  class ConnectivityManager : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ConnectivityManager").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "addHttpRoutePolicy", AddHttpRoutePolicy);
      Nan::SetMethod(constructor, "removeHttpRoutePolicy", RemoveHttpRoutePolicy);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(AcquireConnectionAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("acquireConnectionAsync").ToLocalChecked(), func);

      Nan::Set(exports, Nan::New<String>("ConnectivityManager").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ConnectivityManager(::Windows::Networking::Connectivity::ConnectivityManager^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::ConnectivityManager^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectivityManager^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::ConnectivityManager^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ConnectivityManager *wrapperInstance = new ConnectivityManager(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::ConnectivityManager^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::ConnectivityManager^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::ConnectivityManager^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapConnectivityManager(winRtInstance));
    }


  

    static void AcquireConnectionAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Networking::Connectivity::ConnectionSession^>^ op;
      

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::CellularApnContext^>(info[0]))
      {
        try
        {
          ::Windows::Networking::Connectivity::CellularApnContext^ arg0 = UnwrapCellularApnContext(info[0]);
          
          op = ::Windows::Networking::Connectivity::ConnectivityManager::AcquireConnectionAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Networking::Connectivity::ConnectionSession^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = WrapConnectionSession(result);
            if (tryCatch.HasCaught())
            {
              error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
            }
            else 
            {
              error = Undefined();
            }
            if (arg1.IsEmpty()) arg1 = Undefined();
            Local<Value> args[] = {error, arg1};
			// TODO: this is ugly! Needed due to the possibility of expception occuring inside object convertors
			// can be fixed by wrapping the conversion code in a function and calling it on the fly
			// we must clear the try catch block here so the invoked inner method exception won't get swollen (issue #52) 
			tryCatch.~TryCatch();

	  	    
            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
          
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }

    static void AddHttpRoutePolicy(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::RoutePolicy^>(info[0]))
      {
        try
        {
          ::Windows::Networking::Connectivity::RoutePolicy^ arg0 = UnwrapRoutePolicy(info[0]);
          
          ::Windows::Networking::Connectivity::ConnectivityManager::AddHttpRoutePolicy(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveHttpRoutePolicy(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::RoutePolicy^>(info[0]))
      {
        try
        {
          ::Windows::Networking::Connectivity::RoutePolicy^ arg0 = UnwrapRoutePolicy(info[0]);
          
          ::Windows::Networking::Connectivity::ConnectivityManager::RemoveHttpRoutePolicy(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



  private:
    ::Windows::Networking::Connectivity::ConnectivityManager^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapConnectivityManager(::Windows::Networking::Connectivity::ConnectivityManager^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::ConnectivityManager^ UnwrapConnectivityManager(Local<Value> value);
  };
  Persistent<FunctionTemplate> ConnectivityManager::s_constructorTemplate;

  v8::Local<v8::Value> WrapConnectivityManager(::Windows::Networking::Connectivity::ConnectivityManager^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ConnectivityManager::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::ConnectivityManager^ UnwrapConnectivityManager(Local<Value> value)
  {
     return ConnectivityManager::Unwrap<ConnectivityManager>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitConnectivityManager(Local<Object> exports)
  {
    ConnectivityManager::Init(exports);
  }

  class NetworkStateChangeEventDetails : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("NetworkStateChangeEventDetails").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hasNewConnectionCost").ToLocalChecked(), HasNewConnectionCostGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hasNewDomainConnectivityLevel").ToLocalChecked(), HasNewDomainConnectivityLevelGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hasNewHostNameList").ToLocalChecked(), HasNewHostNameListGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hasNewInternetConnectionProfile").ToLocalChecked(), HasNewInternetConnectionProfileGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hasNewNetworkConnectivityLevel").ToLocalChecked(), HasNewNetworkConnectivityLevelGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hasNewWwanRegistrationState").ToLocalChecked(), HasNewWwanRegistrationStateGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hasNewTetheringClientCount").ToLocalChecked(), HasNewTetheringClientCountGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hasNewTetheringOperationalState").ToLocalChecked(), HasNewTetheringOperationalStateGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("NetworkStateChangeEventDetails").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    NetworkStateChangeEventDetails(::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      NetworkStateChangeEventDetails *wrapperInstance = new NetworkStateChangeEventDetails(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapNetworkStateChangeEventDetails(winRtInstance));
    }


  



    static void HasNewConnectionCostGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^>(info.This()))
      {
        return;
      }

      NetworkStateChangeEventDetails *wrapper = NetworkStateChangeEventDetails::Unwrap<NetworkStateChangeEventDetails>(info.This());

      try 
      {
        bool result = wrapper->_instance->HasNewConnectionCost;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HasNewDomainConnectivityLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^>(info.This()))
      {
        return;
      }

      NetworkStateChangeEventDetails *wrapper = NetworkStateChangeEventDetails::Unwrap<NetworkStateChangeEventDetails>(info.This());

      try 
      {
        bool result = wrapper->_instance->HasNewDomainConnectivityLevel;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HasNewHostNameListGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^>(info.This()))
      {
        return;
      }

      NetworkStateChangeEventDetails *wrapper = NetworkStateChangeEventDetails::Unwrap<NetworkStateChangeEventDetails>(info.This());

      try 
      {
        bool result = wrapper->_instance->HasNewHostNameList;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HasNewInternetConnectionProfileGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^>(info.This()))
      {
        return;
      }

      NetworkStateChangeEventDetails *wrapper = NetworkStateChangeEventDetails::Unwrap<NetworkStateChangeEventDetails>(info.This());

      try 
      {
        bool result = wrapper->_instance->HasNewInternetConnectionProfile;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HasNewNetworkConnectivityLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^>(info.This()))
      {
        return;
      }

      NetworkStateChangeEventDetails *wrapper = NetworkStateChangeEventDetails::Unwrap<NetworkStateChangeEventDetails>(info.This());

      try 
      {
        bool result = wrapper->_instance->HasNewNetworkConnectivityLevel;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HasNewWwanRegistrationStateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^>(info.This()))
      {
        return;
      }

      NetworkStateChangeEventDetails *wrapper = NetworkStateChangeEventDetails::Unwrap<NetworkStateChangeEventDetails>(info.This());

      try 
      {
        bool result = wrapper->_instance->HasNewWwanRegistrationState;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HasNewTetheringClientCountGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^>(info.This()))
      {
        return;
      }

      NetworkStateChangeEventDetails *wrapper = NetworkStateChangeEventDetails::Unwrap<NetworkStateChangeEventDetails>(info.This());

      try 
      {
        bool result = wrapper->_instance->HasNewTetheringClientCount;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HasNewTetheringOperationalStateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^>(info.This()))
      {
        return;
      }

      NetworkStateChangeEventDetails *wrapper = NetworkStateChangeEventDetails::Unwrap<NetworkStateChangeEventDetails>(info.This());

      try 
      {
        bool result = wrapper->_instance->HasNewTetheringOperationalState;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapNetworkStateChangeEventDetails(::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^ UnwrapNetworkStateChangeEventDetails(Local<Value> value);
  };
  Persistent<FunctionTemplate> NetworkStateChangeEventDetails::s_constructorTemplate;

  v8::Local<v8::Value> WrapNetworkStateChangeEventDetails(::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(NetworkStateChangeEventDetails::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::NetworkStateChangeEventDetails^ UnwrapNetworkStateChangeEventDetails(Local<Value> value)
  {
     return NetworkStateChangeEventDetails::Unwrap<NetworkStateChangeEventDetails>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitNetworkStateChangeEventDetails(Local<Object> exports)
  {
    NetworkStateChangeEventDetails::Init(exports);
  }

  class WwanConnectionProfileDetails : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("WwanConnectionProfileDetails").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getNetworkRegistrationState", GetNetworkRegistrationState);
      Nan::SetPrototypeMethod(localRef, "getCurrentDataClass", GetCurrentDataClass);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("accessPointName").ToLocalChecked(), AccessPointNameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("homeProviderId").ToLocalChecked(), HomeProviderIdGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("WwanConnectionProfileDetails").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    WwanConnectionProfileDetails(::Windows::Networking::Connectivity::WwanConnectionProfileDetails^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::Networking::Connectivity::WwanConnectionProfileDetails^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::WwanConnectionProfileDetails^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Networking::Connectivity::WwanConnectionProfileDetails^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      WwanConnectionProfileDetails *wrapperInstance = new WwanConnectionProfileDetails(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::WwanConnectionProfileDetails^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Networking::Connectivity::WwanConnectionProfileDetails^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Networking::Connectivity::WwanConnectionProfileDetails^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapWwanConnectionProfileDetails(winRtInstance));
    }


  
    static void GetNetworkRegistrationState(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::WwanConnectionProfileDetails^>(info.This()))
      {
        return;
      }

      WwanConnectionProfileDetails *wrapper = WwanConnectionProfileDetails::Unwrap<WwanConnectionProfileDetails>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Networking::Connectivity::WwanNetworkRegistrationState result;
          result = wrapper->_instance->GetNetworkRegistrationState();
          info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetCurrentDataClass(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::WwanConnectionProfileDetails^>(info.This()))
      {
        return;
      }

      WwanConnectionProfileDetails *wrapper = WwanConnectionProfileDetails::Unwrap<WwanConnectionProfileDetails>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Networking::Connectivity::WwanDataClass result;
          result = wrapper->_instance->GetCurrentDataClass();
          info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void AccessPointNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::WwanConnectionProfileDetails^>(info.This()))
      {
        return;
      }

      WwanConnectionProfileDetails *wrapper = WwanConnectionProfileDetails::Unwrap<WwanConnectionProfileDetails>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->AccessPointName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HomeProviderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Networking::Connectivity::WwanConnectionProfileDetails^>(info.This()))
      {
        return;
      }

      WwanConnectionProfileDetails *wrapper = WwanConnectionProfileDetails::Unwrap<WwanConnectionProfileDetails>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->HomeProviderId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Networking::Connectivity::WwanConnectionProfileDetails^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapWwanConnectionProfileDetails(::Windows::Networking::Connectivity::WwanConnectionProfileDetails^ wintRtInstance);
    friend ::Windows::Networking::Connectivity::WwanConnectionProfileDetails^ UnwrapWwanConnectionProfileDetails(Local<Value> value);
  };
  Persistent<FunctionTemplate> WwanConnectionProfileDetails::s_constructorTemplate;

  v8::Local<v8::Value> WrapWwanConnectionProfileDetails(::Windows::Networking::Connectivity::WwanConnectionProfileDetails^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(WwanConnectionProfileDetails::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Networking::Connectivity::WwanConnectionProfileDetails^ UnwrapWwanConnectionProfileDetails(Local<Value> value)
  {
     return WwanConnectionProfileDetails::Unwrap<WwanConnectionProfileDetails>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitWwanConnectionProfileDetails(Local<Object> exports)
  {
    WwanConnectionProfileDetails::Init(exports);
  }

} } } } 

NAN_MODULE_INIT(init)
{
  // we ignore failures for now since it probably means that the initialization already happened for STA, and that's cool
  CoInitializeEx(nullptr, COINIT_MULTITHREADED);
  //if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
  /*{
    Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"error in CoInitializeEx()")));
    return;
  }*/
  
  NodeRT::Windows::Networking::Connectivity::InitNetworkCostTypeEnum(target);
  NodeRT::Windows::Networking::Connectivity::InitNetworkConnectivityLevelEnum(target);
  NodeRT::Windows::Networking::Connectivity::InitNetworkTypesEnum(target);
  NodeRT::Windows::Networking::Connectivity::InitRoamingStatesEnum(target);
  NodeRT::Windows::Networking::Connectivity::InitNetworkAuthenticationTypeEnum(target);
  NodeRT::Windows::Networking::Connectivity::InitNetworkEncryptionTypeEnum(target);
  NodeRT::Windows::Networking::Connectivity::InitDomainConnectivityLevelEnum(target);
  NodeRT::Windows::Networking::Connectivity::InitDataUsageGranularityEnum(target);
  NodeRT::Windows::Networking::Connectivity::InitCellularApnAuthenticationTypeEnum(target);
  NodeRT::Windows::Networking::Connectivity::InitTriStatesEnum(target);
  NodeRT::Windows::Networking::Connectivity::InitWwanNetworkRegistrationStateEnum(target);
  NodeRT::Windows::Networking::Connectivity::InitWwanDataClassEnum(target);
  NodeRT::Windows::Networking::Connectivity::InitIPInformation(target);
  NodeRT::Windows::Networking::Connectivity::InitDataPlanUsage(target);
  NodeRT::Windows::Networking::Connectivity::InitConnectionCost(target);
  NodeRT::Windows::Networking::Connectivity::InitDataPlanStatus(target);
  NodeRT::Windows::Networking::Connectivity::InitNetworkAdapter(target);
  NodeRT::Windows::Networking::Connectivity::InitDataUsage(target);
  NodeRT::Windows::Networking::Connectivity::InitNetworkSecuritySettings(target);
  NodeRT::Windows::Networking::Connectivity::InitWlanConnectionProfileDetails(target);
  NodeRT::Windows::Networking::Connectivity::InitNetworkUsage(target);
  NodeRT::Windows::Networking::Connectivity::InitConnectivityInterval(target);
  NodeRT::Windows::Networking::Connectivity::InitAttributedNetworkUsage(target);
  NodeRT::Windows::Networking::Connectivity::InitLanIdentifierData(target);
  NodeRT::Windows::Networking::Connectivity::InitConnectionProfile(target);
  NodeRT::Windows::Networking::Connectivity::InitLanIdentifier(target);
  NodeRT::Windows::Networking::Connectivity::InitProxyConfiguration(target);
  NodeRT::Windows::Networking::Connectivity::InitConnectionProfileFilter(target);
  NodeRT::Windows::Networking::Connectivity::InitNetworkItem(target);
  NodeRT::Windows::Networking::Connectivity::InitRoutePolicy(target);
  NodeRT::Windows::Networking::Connectivity::InitCellularApnContext(target);
  NodeRT::Windows::Networking::Connectivity::InitConnectionSession(target);
  NodeRT::Windows::Networking::Connectivity::InitNetworkInformation(target);
  NodeRT::Windows::Networking::Connectivity::InitConnectivityManager(target);
  NodeRT::Windows::Networking::Connectivity::InitNetworkStateChangeEventDetails(target);
  NodeRT::Windows::Networking::Connectivity::InitWwanConnectionProfileDetails(target);

  NodeRT::Utils::RegisterNameSpace("Windows.Networking.Connectivity", target);
}


NODE_MODULE(binding, init)
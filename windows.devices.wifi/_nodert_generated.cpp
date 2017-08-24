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

namespace NodeRT { namespace Windows { namespace Devices { namespace WiFi { 

  v8::Local<v8::Value> WrapWiFiAdapter(::Windows::Devices::WiFi::WiFiAdapter^ wintRtInstance);
  ::Windows::Devices::WiFi::WiFiAdapter^ UnwrapWiFiAdapter(Local<Value> value);
  
  v8::Local<v8::Value> WrapWiFiNetworkReport(::Windows::Devices::WiFi::WiFiNetworkReport^ wintRtInstance);
  ::Windows::Devices::WiFi::WiFiNetworkReport^ UnwrapWiFiNetworkReport(Local<Value> value);
  
  v8::Local<v8::Value> WrapWiFiAvailableNetwork(::Windows::Devices::WiFi::WiFiAvailableNetwork^ wintRtInstance);
  ::Windows::Devices::WiFi::WiFiAvailableNetwork^ UnwrapWiFiAvailableNetwork(Local<Value> value);
  
  v8::Local<v8::Value> WrapWiFiConnectionResult(::Windows::Devices::WiFi::WiFiConnectionResult^ wintRtInstance);
  ::Windows::Devices::WiFi::WiFiConnectionResult^ UnwrapWiFiConnectionResult(Local<Value> value);
  


  static void InitWiFiNetworkKindEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("WiFiNetworkKind").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("any").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiNetworkKind::Any)));
	Nan::Set(enumObject, Nan::New<String>("infrastructure").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiNetworkKind::Infrastructure)));
	Nan::Set(enumObject, Nan::New<String>("adhoc").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiNetworkKind::Adhoc)));
  }


  static void InitWiFiPhyKindEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("WiFiPhyKind").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("unknown").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiPhyKind::Unknown)));
	Nan::Set(enumObject, Nan::New<String>("fhss").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiPhyKind::Fhss)));
	Nan::Set(enumObject, Nan::New<String>("dsss").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiPhyKind::Dsss)));
	Nan::Set(enumObject, Nan::New<String>("iRBaseband").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiPhyKind::IRBaseband)));
	Nan::Set(enumObject, Nan::New<String>("ofdm").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiPhyKind::Ofdm)));
	Nan::Set(enumObject, Nan::New<String>("hrdsss").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiPhyKind::Hrdsss)));
	Nan::Set(enumObject, Nan::New<String>("erp").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiPhyKind::Erp)));
	Nan::Set(enumObject, Nan::New<String>("hT").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiPhyKind::HT)));
	Nan::Set(enumObject, Nan::New<String>("vht").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiPhyKind::Vht)));
	Nan::Set(enumObject, Nan::New<String>("dmg").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiPhyKind::Dmg)));
  }


  static void InitWiFiAccessStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("WiFiAccessStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("unspecified").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiAccessStatus::Unspecified)));
	Nan::Set(enumObject, Nan::New<String>("allowed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiAccessStatus::Allowed)));
	Nan::Set(enumObject, Nan::New<String>("deniedByUser").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiAccessStatus::DeniedByUser)));
	Nan::Set(enumObject, Nan::New<String>("deniedBySystem").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiAccessStatus::DeniedBySystem)));
  }


  static void InitWiFiReconnectionKindEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("WiFiReconnectionKind").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("automatic").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiReconnectionKind::Automatic)));
	Nan::Set(enumObject, Nan::New<String>("manual").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiReconnectionKind::Manual)));
  }


  static void InitWiFiConnectionStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("WiFiConnectionStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("unspecifiedFailure").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiConnectionStatus::UnspecifiedFailure)));
	Nan::Set(enumObject, Nan::New<String>("success").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiConnectionStatus::Success)));
	Nan::Set(enumObject, Nan::New<String>("accessRevoked").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiConnectionStatus::AccessRevoked)));
	Nan::Set(enumObject, Nan::New<String>("invalidCredential").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiConnectionStatus::InvalidCredential)));
	Nan::Set(enumObject, Nan::New<String>("networkNotAvailable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiConnectionStatus::NetworkNotAvailable)));
	Nan::Set(enumObject, Nan::New<String>("timeout").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiConnectionStatus::Timeout)));
	Nan::Set(enumObject, Nan::New<String>("unsupportedAuthenticationProtocol").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::WiFi::WiFiConnectionStatus::UnsupportedAuthenticationProtocol)));
  }



  
  class WiFiAdapter : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("WiFiAdapter").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "disconnect", Disconnect);
      
            
      Nan::SetPrototypeMethod(localRef, "scanAsync", ScanAsync);
      Nan::SetPrototypeMethod(localRef, "connectAsync", ConnectAsync);
      
            
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("networkAdapter").ToLocalChecked(), NetworkAdapterGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("networkReport").ToLocalChecked(), NetworkReportGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "getDeviceSelector", GetDeviceSelector);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(FindAllAdaptersAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("findAllAdaptersAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(FromIdAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("fromIdAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(RequestAccessAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("requestAccessAsync").ToLocalChecked(), func);

      Nan::Set(exports, Nan::New<String>("WiFiAdapter").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    WiFiAdapter(::Windows::Devices::WiFi::WiFiAdapter^ instance)
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
      
      ::Windows::Devices::WiFi::WiFiAdapter^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAdapter^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::WiFi::WiFiAdapter^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      WiFiAdapter *wrapperInstance = new WiFiAdapter(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAdapter^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::WiFi::WiFiAdapter^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::WiFi::WiFiAdapter^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapWiFiAdapter(winRtInstance));
    }


    static void ScanAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAdapter^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      WiFiAdapter *wrapper = WiFiAdapter::Unwrap<WiFiAdapter>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->ScanAsync();
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

      opTask.then( [asyncToken] (task<void> t) 
      {	
        try
        {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};

		    
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
    static void ConnectAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAdapter^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      WiFiAdapter *wrapper = WiFiAdapter::Unwrap<WiFiAdapter>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::WiFi::WiFiConnectionResult^>^ op;
    

      if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Devices::WiFi::WiFiAvailableNetwork^ arg0 = UnwrapWiFiAvailableNetwork(info[0]);
          ::Windows::Devices::WiFi::WiFiReconnectionKind arg1 = static_cast<::Windows::Devices::WiFi::WiFiReconnectionKind>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->ConnectAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info[0])
        && info[1]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(info[2]))
      {
        try
        {
          ::Windows::Devices::WiFi::WiFiAvailableNetwork^ arg0 = UnwrapWiFiAvailableNetwork(info[0]);
          ::Windows::Devices::WiFi::WiFiReconnectionKind arg1 = static_cast<::Windows::Devices::WiFi::WiFiReconnectionKind>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          ::Windows::Security::Credentials::PasswordCredential^ arg2 = dynamic_cast<::Windows::Security::Credentials::PasswordCredential^>(NodeRT::Utils::GetObjectInstance(info[2]));
          
          op = wrapper->_instance->ConnectAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 5
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info[0])
        && info[1]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(info[2])
        && info[3]->IsString())
      {
        try
        {
          ::Windows::Devices::WiFi::WiFiAvailableNetwork^ arg0 = UnwrapWiFiAvailableNetwork(info[0]);
          ::Windows::Devices::WiFi::WiFiReconnectionKind arg1 = static_cast<::Windows::Devices::WiFi::WiFiReconnectionKind>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          ::Windows::Security::Credentials::PasswordCredential^ arg2 = dynamic_cast<::Windows::Security::Credentials::PasswordCredential^>(NodeRT::Utils::GetObjectInstance(info[2]));
          Platform::String^ arg3 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[3])));
          
          op = wrapper->_instance->ConnectAsync(arg0,arg1,arg2,arg3);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::WiFi::WiFiConnectionResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = WrapWiFiConnectionResult(result);
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
  
    static void Disconnect(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAdapter^>(info.This()))
      {
        return;
      }

      WiFiAdapter *wrapper = WiFiAdapter::Unwrap<WiFiAdapter>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Disconnect();
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

    static void FindAllAdaptersAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Devices::WiFi::WiFiAdapter^>^>^ op;
      

      if (info.Length() == 1)
      {
        try
        {
          op = ::Windows::Devices::WiFi::WiFiAdapter::FindAllAdaptersAsync();
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

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Devices::WiFi::WiFiAdapter^>^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Devices::WiFi::WiFiAdapter^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::WiFi::WiFiAdapter^ val) -> Local<Value> {
              return WrapWiFiAdapter(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAdapter^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::WiFi::WiFiAdapter^ {
              return UnwrapWiFiAdapter(value);
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
    static void FromIdAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::WiFi::WiFiAdapter^>^ op;
      

      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          op = ::Windows::Devices::WiFi::WiFiAdapter::FromIdAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Devices::WiFi::WiFiAdapter^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = WrapWiFiAdapter(result);
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
    static void RequestAccessAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::WiFi::WiFiAccessStatus>^ op;
      

      if (info.Length() == 1)
      {
        try
        {
          op = ::Windows::Devices::WiFi::WiFiAdapter::RequestAccessAsync();
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

      opTask.then( [asyncToken] (task<::Windows::Devices::WiFi::WiFiAccessStatus> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = Nan::New<Integer>(static_cast<int>(result));
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

    static void GetDeviceSelector(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = ::Windows::Devices::WiFi::WiFiAdapter::GetDeviceSelector();
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

    static void NetworkAdapterGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAdapter^>(info.This()))
      {
        return;
      }

      WiFiAdapter *wrapper = WiFiAdapter::Unwrap<WiFiAdapter>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::NetworkAdapter^ result = wrapper->_instance->NetworkAdapter;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Networking.Connectivity", "NetworkAdapter", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NetworkReportGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAdapter^>(info.This()))
      {
        return;
      }

      WiFiAdapter *wrapper = WiFiAdapter::Unwrap<WiFiAdapter>(info.This());

      try 
      {
        ::Windows::Devices::WiFi::WiFiNetworkReport^ result = wrapper->_instance->NetworkReport;
        info.GetReturnValue().Set(WrapWiFiNetworkReport(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
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
      if (NodeRT::Utils::CaseInsenstiveEquals(L"availableNetworksChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAdapter^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        WiFiAdapter *wrapper = WiFiAdapter::Unwrap<WiFiAdapter>(info.This());
      
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

          registrationToken = wrapper->_instance->AvailableNetworksChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::WiFi::WiFiAdapter^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Devices::WiFi::WiFiAdapter^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
           	    HandleScope scope;
                TryCatch tryCatch;
              
                Local<Value> error;

                Local<Value> wrappedArg0 = WrapWiFiAdapter(arg0);
                Local<Value> wrappedArg1 = CreateOpaqueWrapper(arg1);

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
                if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
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

      if ((NodeRT::Utils::CaseInsenstiveEquals(L"availableNetworksChanged", str)))
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"availableNetworksChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAdapter^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          WiFiAdapter *wrapper = WiFiAdapter::Unwrap<WiFiAdapter>(info.This());
          wrapper->_instance->AvailableNetworksChanged::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::WiFi::WiFiAdapter^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapWiFiAdapter(::Windows::Devices::WiFi::WiFiAdapter^ wintRtInstance);
    friend ::Windows::Devices::WiFi::WiFiAdapter^ UnwrapWiFiAdapter(Local<Value> value);
  };
  Persistent<FunctionTemplate> WiFiAdapter::s_constructorTemplate;

  v8::Local<v8::Value> WrapWiFiAdapter(::Windows::Devices::WiFi::WiFiAdapter^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(WiFiAdapter::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::WiFi::WiFiAdapter^ UnwrapWiFiAdapter(Local<Value> value)
  {
     return WiFiAdapter::Unwrap<WiFiAdapter>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitWiFiAdapter(Local<Object> exports)
  {
    WiFiAdapter::Init(exports);
  }

  class WiFiNetworkReport : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("WiFiNetworkReport").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("availableNetworks").ToLocalChecked(), AvailableNetworksGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("timestamp").ToLocalChecked(), TimestampGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("WiFiNetworkReport").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    WiFiNetworkReport(::Windows::Devices::WiFi::WiFiNetworkReport^ instance)
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
      
      ::Windows::Devices::WiFi::WiFiNetworkReport^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiNetworkReport^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::WiFi::WiFiNetworkReport^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      WiFiNetworkReport *wrapperInstance = new WiFiNetworkReport(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiNetworkReport^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::WiFi::WiFiNetworkReport^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::WiFi::WiFiNetworkReport^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapWiFiNetworkReport(winRtInstance));
    }


  



    static void AvailableNetworksGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiNetworkReport^>(info.This()))
      {
        return;
      }

      WiFiNetworkReport *wrapper = WiFiNetworkReport::Unwrap<WiFiNetworkReport>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::WiFi::WiFiAvailableNetwork^>^ result = wrapper->_instance->AvailableNetworks;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::WiFi::WiFiAvailableNetwork^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::WiFi::WiFiAvailableNetwork^ val) -> Local<Value> {
              return WrapWiFiAvailableNetwork(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::WiFi::WiFiAvailableNetwork^ {
              return UnwrapWiFiAvailableNetwork(value);
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
    
    static void TimestampGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiNetworkReport^>(info.This()))
      {
        return;
      }

      WiFiNetworkReport *wrapper = WiFiNetworkReport::Unwrap<WiFiNetworkReport>(info.This());

      try 
      {
        ::Windows::Foundation::DateTime result = wrapper->_instance->Timestamp;
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
    ::Windows::Devices::WiFi::WiFiNetworkReport^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapWiFiNetworkReport(::Windows::Devices::WiFi::WiFiNetworkReport^ wintRtInstance);
    friend ::Windows::Devices::WiFi::WiFiNetworkReport^ UnwrapWiFiNetworkReport(Local<Value> value);
  };
  Persistent<FunctionTemplate> WiFiNetworkReport::s_constructorTemplate;

  v8::Local<v8::Value> WrapWiFiNetworkReport(::Windows::Devices::WiFi::WiFiNetworkReport^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(WiFiNetworkReport::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::WiFi::WiFiNetworkReport^ UnwrapWiFiNetworkReport(Local<Value> value)
  {
     return WiFiNetworkReport::Unwrap<WiFiNetworkReport>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitWiFiNetworkReport(Local<Object> exports)
  {
    WiFiNetworkReport::Init(exports);
  }

  class WiFiAvailableNetwork : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("WiFiAvailableNetwork").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("beaconInterval").ToLocalChecked(), BeaconIntervalGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bssid").ToLocalChecked(), BssidGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("channelCenterFrequencyInKilohertz").ToLocalChecked(), ChannelCenterFrequencyInKilohertzGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isWiFiDirect").ToLocalChecked(), IsWiFiDirectGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("networkKind").ToLocalChecked(), NetworkKindGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("networkRssiInDecibelMilliwatts").ToLocalChecked(), NetworkRssiInDecibelMilliwattsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("phyKind").ToLocalChecked(), PhyKindGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("securitySettings").ToLocalChecked(), SecuritySettingsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("signalBars").ToLocalChecked(), SignalBarsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("ssid").ToLocalChecked(), SsidGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("uptime").ToLocalChecked(), UptimeGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("WiFiAvailableNetwork").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    WiFiAvailableNetwork(::Windows::Devices::WiFi::WiFiAvailableNetwork^ instance)
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
      
      ::Windows::Devices::WiFi::WiFiAvailableNetwork^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::WiFi::WiFiAvailableNetwork^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      WiFiAvailableNetwork *wrapperInstance = new WiFiAvailableNetwork(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::WiFi::WiFiAvailableNetwork^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::WiFi::WiFiAvailableNetwork^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapWiFiAvailableNetwork(winRtInstance));
    }


  



    static void BeaconIntervalGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info.This()))
      {
        return;
      }

      WiFiAvailableNetwork *wrapper = WiFiAvailableNetwork::Unwrap<WiFiAvailableNetwork>(info.This());

      try 
      {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->BeaconInterval;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BssidGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info.This()))
      {
        return;
      }

      WiFiAvailableNetwork *wrapper = WiFiAvailableNetwork::Unwrap<WiFiAvailableNetwork>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Bssid;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ChannelCenterFrequencyInKilohertzGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info.This()))
      {
        return;
      }

      WiFiAvailableNetwork *wrapper = WiFiAvailableNetwork::Unwrap<WiFiAvailableNetwork>(info.This());

      try 
      {
        int result = wrapper->_instance->ChannelCenterFrequencyInKilohertz;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsWiFiDirectGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info.This()))
      {
        return;
      }

      WiFiAvailableNetwork *wrapper = WiFiAvailableNetwork::Unwrap<WiFiAvailableNetwork>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsWiFiDirect;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NetworkKindGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info.This()))
      {
        return;
      }

      WiFiAvailableNetwork *wrapper = WiFiAvailableNetwork::Unwrap<WiFiAvailableNetwork>(info.This());

      try 
      {
        ::Windows::Devices::WiFi::WiFiNetworkKind result = wrapper->_instance->NetworkKind;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NetworkRssiInDecibelMilliwattsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info.This()))
      {
        return;
      }

      WiFiAvailableNetwork *wrapper = WiFiAvailableNetwork::Unwrap<WiFiAvailableNetwork>(info.This());

      try 
      {
        double result = wrapper->_instance->NetworkRssiInDecibelMilliwatts;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PhyKindGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info.This()))
      {
        return;
      }

      WiFiAvailableNetwork *wrapper = WiFiAvailableNetwork::Unwrap<WiFiAvailableNetwork>(info.This());

      try 
      {
        ::Windows::Devices::WiFi::WiFiPhyKind result = wrapper->_instance->PhyKind;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SecuritySettingsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info.This()))
      {
        return;
      }

      WiFiAvailableNetwork *wrapper = WiFiAvailableNetwork::Unwrap<WiFiAvailableNetwork>(info.This());

      try 
      {
        ::Windows::Networking::Connectivity::NetworkSecuritySettings^ result = wrapper->_instance->SecuritySettings;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Networking.Connectivity", "NetworkSecuritySettings", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SignalBarsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info.This()))
      {
        return;
      }

      WiFiAvailableNetwork *wrapper = WiFiAvailableNetwork::Unwrap<WiFiAvailableNetwork>(info.This());

      try 
      {
        unsigned char result = wrapper->_instance->SignalBars;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SsidGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info.This()))
      {
        return;
      }

      WiFiAvailableNetwork *wrapper = WiFiAvailableNetwork::Unwrap<WiFiAvailableNetwork>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Ssid;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UptimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiAvailableNetwork^>(info.This()))
      {
        return;
      }

      WiFiAvailableNetwork *wrapper = WiFiAvailableNetwork::Unwrap<WiFiAvailableNetwork>(info.This());

      try 
      {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->Uptime;
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
    ::Windows::Devices::WiFi::WiFiAvailableNetwork^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapWiFiAvailableNetwork(::Windows::Devices::WiFi::WiFiAvailableNetwork^ wintRtInstance);
    friend ::Windows::Devices::WiFi::WiFiAvailableNetwork^ UnwrapWiFiAvailableNetwork(Local<Value> value);
  };
  Persistent<FunctionTemplate> WiFiAvailableNetwork::s_constructorTemplate;

  v8::Local<v8::Value> WrapWiFiAvailableNetwork(::Windows::Devices::WiFi::WiFiAvailableNetwork^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(WiFiAvailableNetwork::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::WiFi::WiFiAvailableNetwork^ UnwrapWiFiAvailableNetwork(Local<Value> value)
  {
     return WiFiAvailableNetwork::Unwrap<WiFiAvailableNetwork>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitWiFiAvailableNetwork(Local<Object> exports)
  {
    WiFiAvailableNetwork::Init(exports);
  }

  class WiFiConnectionResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("WiFiConnectionResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("connectionStatus").ToLocalChecked(), ConnectionStatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("WiFiConnectionResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    WiFiConnectionResult(::Windows::Devices::WiFi::WiFiConnectionResult^ instance)
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
      
      ::Windows::Devices::WiFi::WiFiConnectionResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiConnectionResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::WiFi::WiFiConnectionResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      WiFiConnectionResult *wrapperInstance = new WiFiConnectionResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiConnectionResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Devices::WiFi::WiFiConnectionResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Devices::WiFi::WiFiConnectionResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapWiFiConnectionResult(winRtInstance));
    }


  



    static void ConnectionStatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::WiFi::WiFiConnectionResult^>(info.This()))
      {
        return;
      }

      WiFiConnectionResult *wrapper = WiFiConnectionResult::Unwrap<WiFiConnectionResult>(info.This());

      try 
      {
        ::Windows::Devices::WiFi::WiFiConnectionStatus result = wrapper->_instance->ConnectionStatus;
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
    ::Windows::Devices::WiFi::WiFiConnectionResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapWiFiConnectionResult(::Windows::Devices::WiFi::WiFiConnectionResult^ wintRtInstance);
    friend ::Windows::Devices::WiFi::WiFiConnectionResult^ UnwrapWiFiConnectionResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> WiFiConnectionResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapWiFiConnectionResult(::Windows::Devices::WiFi::WiFiConnectionResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(WiFiConnectionResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::WiFi::WiFiConnectionResult^ UnwrapWiFiConnectionResult(Local<Value> value)
  {
     return WiFiConnectionResult::Unwrap<WiFiConnectionResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitWiFiConnectionResult(Local<Object> exports)
  {
    WiFiConnectionResult::Init(exports);
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
  
  NodeRT::Windows::Devices::WiFi::InitWiFiNetworkKindEnum(target);
  NodeRT::Windows::Devices::WiFi::InitWiFiPhyKindEnum(target);
  NodeRT::Windows::Devices::WiFi::InitWiFiAccessStatusEnum(target);
  NodeRT::Windows::Devices::WiFi::InitWiFiReconnectionKindEnum(target);
  NodeRT::Windows::Devices::WiFi::InitWiFiConnectionStatusEnum(target);
  NodeRT::Windows::Devices::WiFi::InitWiFiAdapter(target);
  NodeRT::Windows::Devices::WiFi::InitWiFiNetworkReport(target);
  NodeRT::Windows::Devices::WiFi::InitWiFiAvailableNetwork(target);
  NodeRT::Windows::Devices::WiFi::InitWiFiConnectionResult(target);

  NodeRT::Utils::RegisterNameSpace("Windows.Devices.WiFi", target);
}


NODE_MODULE(binding, init)
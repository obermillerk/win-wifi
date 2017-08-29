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

namespace NodeRT { namespace Windows { namespace Security { namespace Credentials { 

  v8::Local<v8::Value> WrapKeyCredentialRetrievalResult(::Windows::Security::Credentials::KeyCredentialRetrievalResult^ wintRtInstance);
  ::Windows::Security::Credentials::KeyCredentialRetrievalResult^ UnwrapKeyCredentialRetrievalResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapKeyCredentialOperationResult(::Windows::Security::Credentials::KeyCredentialOperationResult^ wintRtInstance);
  ::Windows::Security::Credentials::KeyCredentialOperationResult^ UnwrapKeyCredentialOperationResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapKeyCredentialAttestationResult(::Windows::Security::Credentials::KeyCredentialAttestationResult^ wintRtInstance);
  ::Windows::Security::Credentials::KeyCredentialAttestationResult^ UnwrapKeyCredentialAttestationResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapKeyCredential(::Windows::Security::Credentials::KeyCredential^ wintRtInstance);
  ::Windows::Security::Credentials::KeyCredential^ UnwrapKeyCredential(Local<Value> value);
  
  v8::Local<v8::Value> WrapKeyCredentialManager(::Windows::Security::Credentials::KeyCredentialManager^ wintRtInstance);
  ::Windows::Security::Credentials::KeyCredentialManager^ UnwrapKeyCredentialManager(Local<Value> value);
  
  v8::Local<v8::Value> WrapWebAccountProvider(::Windows::Security::Credentials::WebAccountProvider^ wintRtInstance);
  ::Windows::Security::Credentials::WebAccountProvider^ UnwrapWebAccountProvider(Local<Value> value);
  
  v8::Local<v8::Value> WrapWebAccount(::Windows::Security::Credentials::WebAccount^ wintRtInstance);
  ::Windows::Security::Credentials::WebAccount^ UnwrapWebAccount(Local<Value> value);
  
  v8::Local<v8::Value> WrapIWebAccount(::Windows::Security::Credentials::IWebAccount^ wintRtInstance);
  ::Windows::Security::Credentials::IWebAccount^ UnwrapIWebAccount(Local<Value> value);
  
  v8::Local<v8::Value> WrapPasswordCredential(::Windows::Security::Credentials::PasswordCredential^ wintRtInstance);
  ::Windows::Security::Credentials::PasswordCredential^ UnwrapPasswordCredential(Local<Value> value);
  
  v8::Local<v8::Value> WrapPasswordVault(::Windows::Security::Credentials::PasswordVault^ wintRtInstance);
  ::Windows::Security::Credentials::PasswordVault^ UnwrapPasswordVault(Local<Value> value);
  
  v8::Local<v8::Value> WrapPasswordCredentialPropertyStore(::Windows::Security::Credentials::PasswordCredentialPropertyStore^ wintRtInstance);
  ::Windows::Security::Credentials::PasswordCredentialPropertyStore^ UnwrapPasswordCredentialPropertyStore(Local<Value> value);
  


  static void InitKeyCredentialStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("KeyCredentialStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("success").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::KeyCredentialStatus::Success)));
	Nan::Set(enumObject, Nan::New<String>("unknownError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::KeyCredentialStatus::UnknownError)));
	Nan::Set(enumObject, Nan::New<String>("notFound").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::KeyCredentialStatus::NotFound)));
	Nan::Set(enumObject, Nan::New<String>("userCanceled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::KeyCredentialStatus::UserCanceled)));
	Nan::Set(enumObject, Nan::New<String>("userPrefersPassword").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::KeyCredentialStatus::UserPrefersPassword)));
	Nan::Set(enumObject, Nan::New<String>("credentialAlreadyExists").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::KeyCredentialStatus::CredentialAlreadyExists)));
	Nan::Set(enumObject, Nan::New<String>("securityDeviceLocked").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::KeyCredentialStatus::SecurityDeviceLocked)));
  }


  static void InitKeyCredentialAttestationStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("KeyCredentialAttestationStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("success").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::KeyCredentialAttestationStatus::Success)));
	Nan::Set(enumObject, Nan::New<String>("unknownError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::KeyCredentialAttestationStatus::UnknownError)));
	Nan::Set(enumObject, Nan::New<String>("notSupported").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::KeyCredentialAttestationStatus::NotSupported)));
	Nan::Set(enumObject, Nan::New<String>("temporaryFailure").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::KeyCredentialAttestationStatus::TemporaryFailure)));
  }


  static void InitKeyCredentialCreationOptionEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("KeyCredentialCreationOption").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("replaceExisting").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::KeyCredentialCreationOption::ReplaceExisting)));
	Nan::Set(enumObject, Nan::New<String>("failIfExists").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::KeyCredentialCreationOption::FailIfExists)));
  }


  static void InitWebAccountStateEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("WebAccountState").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::WebAccountState::None)));
	Nan::Set(enumObject, Nan::New<String>("connected").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::WebAccountState::Connected)));
	Nan::Set(enumObject, Nan::New<String>("error").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::WebAccountState::Error)));
  }


  static void InitWebAccountPictureSizeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("WebAccountPictureSize").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("size64x64").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::WebAccountPictureSize::Size64x64)));
	Nan::Set(enumObject, Nan::New<String>("size208x208").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::WebAccountPictureSize::Size208x208)));
	Nan::Set(enumObject, Nan::New<String>("size424x424").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::WebAccountPictureSize::Size424x424)));
	Nan::Set(enumObject, Nan::New<String>("size1080x1080").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Security::Credentials::WebAccountPictureSize::Size1080x1080)));
  }



  
  class KeyCredentialRetrievalResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("KeyCredentialRetrievalResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("credential").ToLocalChecked(), CredentialGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("KeyCredentialRetrievalResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    KeyCredentialRetrievalResult(::Windows::Security::Credentials::KeyCredentialRetrievalResult^ instance)
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
      
      ::Windows::Security::Credentials::KeyCredentialRetrievalResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredentialRetrievalResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Security::Credentials::KeyCredentialRetrievalResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      KeyCredentialRetrievalResult *wrapperInstance = new KeyCredentialRetrievalResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredentialRetrievalResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Security::Credentials::KeyCredentialRetrievalResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Security::Credentials::KeyCredentialRetrievalResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapKeyCredentialRetrievalResult(winRtInstance));
    }


  



    static void CredentialGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredentialRetrievalResult^>(info.This()))
      {
        return;
      }

      KeyCredentialRetrievalResult *wrapper = KeyCredentialRetrievalResult::Unwrap<KeyCredentialRetrievalResult>(info.This());

      try 
      {
        ::Windows::Security::Credentials::KeyCredential^ result = wrapper->_instance->Credential;
        info.GetReturnValue().Set(WrapKeyCredential(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredentialRetrievalResult^>(info.This()))
      {
        return;
      }

      KeyCredentialRetrievalResult *wrapper = KeyCredentialRetrievalResult::Unwrap<KeyCredentialRetrievalResult>(info.This());

      try 
      {
        ::Windows::Security::Credentials::KeyCredentialStatus result = wrapper->_instance->Status;
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
    ::Windows::Security::Credentials::KeyCredentialRetrievalResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapKeyCredentialRetrievalResult(::Windows::Security::Credentials::KeyCredentialRetrievalResult^ wintRtInstance);
    friend ::Windows::Security::Credentials::KeyCredentialRetrievalResult^ UnwrapKeyCredentialRetrievalResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> KeyCredentialRetrievalResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapKeyCredentialRetrievalResult(::Windows::Security::Credentials::KeyCredentialRetrievalResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(KeyCredentialRetrievalResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Security::Credentials::KeyCredentialRetrievalResult^ UnwrapKeyCredentialRetrievalResult(Local<Value> value)
  {
     return KeyCredentialRetrievalResult::Unwrap<KeyCredentialRetrievalResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitKeyCredentialRetrievalResult(Local<Object> exports)
  {
    KeyCredentialRetrievalResult::Init(exports);
  }

  class KeyCredentialOperationResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("KeyCredentialOperationResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("result").ToLocalChecked(), ResultGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("KeyCredentialOperationResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    KeyCredentialOperationResult(::Windows::Security::Credentials::KeyCredentialOperationResult^ instance)
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
      
      ::Windows::Security::Credentials::KeyCredentialOperationResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredentialOperationResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Security::Credentials::KeyCredentialOperationResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      KeyCredentialOperationResult *wrapperInstance = new KeyCredentialOperationResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredentialOperationResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Security::Credentials::KeyCredentialOperationResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Security::Credentials::KeyCredentialOperationResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapKeyCredentialOperationResult(winRtInstance));
    }


  



    static void ResultGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredentialOperationResult^>(info.This()))
      {
        return;
      }

      KeyCredentialOperationResult *wrapper = KeyCredentialOperationResult::Unwrap<KeyCredentialOperationResult>(info.This());

      try 
      {
        ::Windows::Storage::Streams::IBuffer^ result = wrapper->_instance->Result;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredentialOperationResult^>(info.This()))
      {
        return;
      }

      KeyCredentialOperationResult *wrapper = KeyCredentialOperationResult::Unwrap<KeyCredentialOperationResult>(info.This());

      try 
      {
        ::Windows::Security::Credentials::KeyCredentialStatus result = wrapper->_instance->Status;
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
    ::Windows::Security::Credentials::KeyCredentialOperationResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapKeyCredentialOperationResult(::Windows::Security::Credentials::KeyCredentialOperationResult^ wintRtInstance);
    friend ::Windows::Security::Credentials::KeyCredentialOperationResult^ UnwrapKeyCredentialOperationResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> KeyCredentialOperationResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapKeyCredentialOperationResult(::Windows::Security::Credentials::KeyCredentialOperationResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(KeyCredentialOperationResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Security::Credentials::KeyCredentialOperationResult^ UnwrapKeyCredentialOperationResult(Local<Value> value)
  {
     return KeyCredentialOperationResult::Unwrap<KeyCredentialOperationResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitKeyCredentialOperationResult(Local<Object> exports)
  {
    KeyCredentialOperationResult::Init(exports);
  }

  class KeyCredentialAttestationResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("KeyCredentialAttestationResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attestationBuffer").ToLocalChecked(), AttestationBufferGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("certificateChainBuffer").ToLocalChecked(), CertificateChainBufferGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("KeyCredentialAttestationResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    KeyCredentialAttestationResult(::Windows::Security::Credentials::KeyCredentialAttestationResult^ instance)
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
      
      ::Windows::Security::Credentials::KeyCredentialAttestationResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredentialAttestationResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Security::Credentials::KeyCredentialAttestationResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      KeyCredentialAttestationResult *wrapperInstance = new KeyCredentialAttestationResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredentialAttestationResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Security::Credentials::KeyCredentialAttestationResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Security::Credentials::KeyCredentialAttestationResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapKeyCredentialAttestationResult(winRtInstance));
    }


  



    static void AttestationBufferGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredentialAttestationResult^>(info.This()))
      {
        return;
      }

      KeyCredentialAttestationResult *wrapper = KeyCredentialAttestationResult::Unwrap<KeyCredentialAttestationResult>(info.This());

      try 
      {
        ::Windows::Storage::Streams::IBuffer^ result = wrapper->_instance->AttestationBuffer;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CertificateChainBufferGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredentialAttestationResult^>(info.This()))
      {
        return;
      }

      KeyCredentialAttestationResult *wrapper = KeyCredentialAttestationResult::Unwrap<KeyCredentialAttestationResult>(info.This());

      try 
      {
        ::Windows::Storage::Streams::IBuffer^ result = wrapper->_instance->CertificateChainBuffer;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredentialAttestationResult^>(info.This()))
      {
        return;
      }

      KeyCredentialAttestationResult *wrapper = KeyCredentialAttestationResult::Unwrap<KeyCredentialAttestationResult>(info.This());

      try 
      {
        ::Windows::Security::Credentials::KeyCredentialAttestationStatus result = wrapper->_instance->Status;
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
    ::Windows::Security::Credentials::KeyCredentialAttestationResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapKeyCredentialAttestationResult(::Windows::Security::Credentials::KeyCredentialAttestationResult^ wintRtInstance);
    friend ::Windows::Security::Credentials::KeyCredentialAttestationResult^ UnwrapKeyCredentialAttestationResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> KeyCredentialAttestationResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapKeyCredentialAttestationResult(::Windows::Security::Credentials::KeyCredentialAttestationResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(KeyCredentialAttestationResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Security::Credentials::KeyCredentialAttestationResult^ UnwrapKeyCredentialAttestationResult(Local<Value> value)
  {
     return KeyCredentialAttestationResult::Unwrap<KeyCredentialAttestationResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitKeyCredentialAttestationResult(Local<Object> exports)
  {
    KeyCredentialAttestationResult::Init(exports);
  }

  class KeyCredential : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("KeyCredential").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "retrievePublicKey", RetrievePublicKey);
      
            
      Nan::SetPrototypeMethod(localRef, "requestSignAsync", RequestSignAsync);
      Nan::SetPrototypeMethod(localRef, "getAttestationAsync", GetAttestationAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("name").ToLocalChecked(), NameGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("KeyCredential").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    KeyCredential(::Windows::Security::Credentials::KeyCredential^ instance)
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
      
      ::Windows::Security::Credentials::KeyCredential^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredential^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Security::Credentials::KeyCredential^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      KeyCredential *wrapperInstance = new KeyCredential(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredential^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Security::Credentials::KeyCredential^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Security::Credentials::KeyCredential^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapKeyCredential(winRtInstance));
    }


    static void RequestSignAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredential^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      KeyCredential *wrapper = KeyCredential::Unwrap<KeyCredential>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Security::Credentials::KeyCredentialOperationResult^>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = wrapper->_instance->RequestSignAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Security::Credentials::KeyCredentialOperationResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = WrapKeyCredentialOperationResult(result);
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
    static void GetAttestationAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredential^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      KeyCredential *wrapper = KeyCredential::Unwrap<KeyCredential>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Security::Credentials::KeyCredentialAttestationResult^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetAttestationAsync();
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

      opTask.then( [asyncToken] (task<::Windows::Security::Credentials::KeyCredentialAttestationResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = WrapKeyCredentialAttestationResult(result);
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
  
    static void RetrievePublicKey(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredential^>(info.This()))
      {
        return;
      }

      KeyCredential *wrapper = KeyCredential::Unwrap<KeyCredential>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ result;
          result = wrapper->_instance->RetrievePublicKey();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Security::Cryptography::Core::CryptographicPublicKeyBlobType arg0 = static_cast<::Windows::Security::Cryptography::Core::CryptographicPublicKeyBlobType>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Streams::IBuffer^ result;
          result = wrapper->_instance->RetrievePublicKey(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result));
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



    static void NameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredential^>(info.This()))
      {
        return;
      }

      KeyCredential *wrapper = KeyCredential::Unwrap<KeyCredential>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Name;
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
    ::Windows::Security::Credentials::KeyCredential^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapKeyCredential(::Windows::Security::Credentials::KeyCredential^ wintRtInstance);
    friend ::Windows::Security::Credentials::KeyCredential^ UnwrapKeyCredential(Local<Value> value);
  };
  Persistent<FunctionTemplate> KeyCredential::s_constructorTemplate;

  v8::Local<v8::Value> WrapKeyCredential(::Windows::Security::Credentials::KeyCredential^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(KeyCredential::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Security::Credentials::KeyCredential^ UnwrapKeyCredential(Local<Value> value)
  {
     return KeyCredential::Unwrap<KeyCredential>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitKeyCredential(Local<Object> exports)
  {
    KeyCredential::Init(exports);
  }

  class KeyCredentialManager : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("KeyCredentialManager").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      func = Nan::GetFunction(Nan::New<FunctionTemplate>(IsSupportedAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("isSupportedAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(RenewAttestationAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("renewAttestationAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(RequestCreateAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("requestCreateAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(OpenAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("openAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(DeleteAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("deleteAsync").ToLocalChecked(), func);

      Nan::Set(exports, Nan::New<String>("KeyCredentialManager").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    KeyCredentialManager(::Windows::Security::Credentials::KeyCredentialManager^ instance)
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
      
      ::Windows::Security::Credentials::KeyCredentialManager^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredentialManager^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Security::Credentials::KeyCredentialManager^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      KeyCredentialManager *wrapperInstance = new KeyCredentialManager(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::KeyCredentialManager^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Security::Credentials::KeyCredentialManager^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Security::Credentials::KeyCredentialManager^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapKeyCredentialManager(winRtInstance));
    }


  

    static void IsSupportedAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
      

      if (info.Length() == 1)
      {
        try
        {
          op = ::Windows::Security::Credentials::KeyCredentialManager::IsSupportedAsync();
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

      opTask.then( [asyncToken] (task<bool> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = Nan::New<Boolean>(result);
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
    static void RenewAttestationAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncAction^ op;
      

      if (info.Length() == 1)
      {
        try
        {
          op = ::Windows::Security::Credentials::KeyCredentialManager::RenewAttestationAsync();
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
    static void RequestCreateAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Security::Credentials::KeyCredentialRetrievalResult^>^ op;
      

      if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          ::Windows::Security::Credentials::KeyCredentialCreationOption arg1 = static_cast<::Windows::Security::Credentials::KeyCredentialCreationOption>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = ::Windows::Security::Credentials::KeyCredentialManager::RequestCreateAsync(arg0,arg1);
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

      opTask.then( [asyncToken] (task<::Windows::Security::Credentials::KeyCredentialRetrievalResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = WrapKeyCredentialRetrievalResult(result);
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
    static void OpenAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Security::Credentials::KeyCredentialRetrievalResult^>^ op;
      

      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          op = ::Windows::Security::Credentials::KeyCredentialManager::OpenAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Security::Credentials::KeyCredentialRetrievalResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = WrapKeyCredentialRetrievalResult(result);
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
    static void DeleteAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncAction^ op;
      

      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          op = ::Windows::Security::Credentials::KeyCredentialManager::DeleteAsync(arg0);
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




  private:
    ::Windows::Security::Credentials::KeyCredentialManager^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapKeyCredentialManager(::Windows::Security::Credentials::KeyCredentialManager^ wintRtInstance);
    friend ::Windows::Security::Credentials::KeyCredentialManager^ UnwrapKeyCredentialManager(Local<Value> value);
  };
  Persistent<FunctionTemplate> KeyCredentialManager::s_constructorTemplate;

  v8::Local<v8::Value> WrapKeyCredentialManager(::Windows::Security::Credentials::KeyCredentialManager^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(KeyCredentialManager::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Security::Credentials::KeyCredentialManager^ UnwrapKeyCredentialManager(Local<Value> value)
  {
     return KeyCredentialManager::Unwrap<KeyCredentialManager>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitKeyCredentialManager(Local<Object> exports)
  {
    KeyCredentialManager::Init(exports);
  }

  class WebAccountProvider : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("WebAccountProvider").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayName").ToLocalChecked(), DisplayNameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("iconUri").ToLocalChecked(), IconUriGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("authority").ToLocalChecked(), AuthorityGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayPurpose").ToLocalChecked(), DisplayPurposeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("user").ToLocalChecked(), UserGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("WebAccountProvider").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    WebAccountProvider(::Windows::Security::Credentials::WebAccountProvider^ instance)
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
      
      ::Windows::Security::Credentials::WebAccountProvider^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccountProvider^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Security::Credentials::WebAccountProvider^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[2]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[1])));
          ::Windows::Foundation::Uri^ arg2 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[2]));
          
          winRtInstance = ref new ::Windows::Security::Credentials::WebAccountProvider(arg0,arg1,arg2);
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

      WebAccountProvider *wrapperInstance = new WebAccountProvider(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccountProvider^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Security::Credentials::WebAccountProvider^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Security::Credentials::WebAccountProvider^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapWebAccountProvider(winRtInstance));
    }


  



    static void DisplayNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccountProvider^>(info.This()))
      {
        return;
      }

      WebAccountProvider *wrapper = WebAccountProvider::Unwrap<WebAccountProvider>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->DisplayName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IconUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccountProvider^>(info.This()))
      {
        return;
      }

      WebAccountProvider *wrapper = WebAccountProvider::Unwrap<WebAccountProvider>(info.This());

      try 
      {
        ::Windows::Foundation::Uri^ result = wrapper->_instance->IconUri;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccountProvider^>(info.This()))
      {
        return;
      }

      WebAccountProvider *wrapper = WebAccountProvider::Unwrap<WebAccountProvider>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Id;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AuthorityGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccountProvider^>(info.This()))
      {
        return;
      }

      WebAccountProvider *wrapper = WebAccountProvider::Unwrap<WebAccountProvider>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Authority;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DisplayPurposeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccountProvider^>(info.This()))
      {
        return;
      }

      WebAccountProvider *wrapper = WebAccountProvider::Unwrap<WebAccountProvider>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->DisplayPurpose;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UserGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccountProvider^>(info.This()))
      {
        return;
      }

      WebAccountProvider *wrapper = WebAccountProvider::Unwrap<WebAccountProvider>(info.This());

      try 
      {
        ::Windows::System::User^ result = wrapper->_instance->User;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.System", "User", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Security::Credentials::WebAccountProvider^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapWebAccountProvider(::Windows::Security::Credentials::WebAccountProvider^ wintRtInstance);
    friend ::Windows::Security::Credentials::WebAccountProvider^ UnwrapWebAccountProvider(Local<Value> value);
  };
  Persistent<FunctionTemplate> WebAccountProvider::s_constructorTemplate;

  v8::Local<v8::Value> WrapWebAccountProvider(::Windows::Security::Credentials::WebAccountProvider^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(WebAccountProvider::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Security::Credentials::WebAccountProvider^ UnwrapWebAccountProvider(Local<Value> value)
  {
     return WebAccountProvider::Unwrap<WebAccountProvider>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitWebAccountProvider(Local<Object> exports)
  {
    WebAccountProvider::Init(exports);
  }

  class WebAccount : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("WebAccount").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "getPictureAsync", GetPictureAsync);
      Nan::SetPrototypeMethod(localRef, "signOutAsync", SignOutAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("state").ToLocalChecked(), StateGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("userName").ToLocalChecked(), UserNameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("webAccountProvider").ToLocalChecked(), WebAccountProviderGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("properties").ToLocalChecked(), PropertiesGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("WebAccount").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    WebAccount(::Windows::Security::Credentials::WebAccount^ instance)
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
      
      ::Windows::Security::Credentials::WebAccount^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccount^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Security::Credentials::WebAccount^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccountProvider^>(info[0])
        && info[1]->IsString()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Security::Credentials::WebAccountProvider^ arg0 = UnwrapWebAccountProvider(info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[1])));
          ::Windows::Security::Credentials::WebAccountState arg2 = static_cast<::Windows::Security::Credentials::WebAccountState>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Security::Credentials::WebAccount(arg0,arg1,arg2);
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

      WebAccount *wrapperInstance = new WebAccount(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccount^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Security::Credentials::WebAccount^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Security::Credentials::WebAccount^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapWebAccount(winRtInstance));
    }


    static void GetPictureAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccount^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      WebAccount *wrapper = WebAccount::Unwrap<WebAccount>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::Streams::IRandomAccessStream^>^ op;
    

      if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Security::Credentials::WebAccountPictureSize arg0 = static_cast<::Windows::Security::Credentials::WebAccountPictureSize>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->GetPictureAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IRandomAccessStream^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IRandomAccessStream", result);
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
    static void SignOutAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccount^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      WebAccount *wrapper = WebAccount::Unwrap<WebAccount>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->SignOutAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          op = wrapper->_instance->SignOutAsync(arg0);
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
  



    static void StateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccount^>(info.This()))
      {
        return;
      }

      WebAccount *wrapper = WebAccount::Unwrap<WebAccount>(info.This());

      try 
      {
        ::Windows::Security::Credentials::WebAccountState result = wrapper->_instance->State;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UserNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccount^>(info.This()))
      {
        return;
      }

      WebAccount *wrapper = WebAccount::Unwrap<WebAccount>(info.This());

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
    
    static void WebAccountProviderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccount^>(info.This()))
      {
        return;
      }

      WebAccount *wrapper = WebAccount::Unwrap<WebAccount>(info.This());

      try 
      {
        ::Windows::Security::Credentials::WebAccountProvider^ result = wrapper->_instance->WebAccountProvider;
        info.GetReturnValue().Set(WrapWebAccountProvider(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccount^>(info.This()))
      {
        return;
      }

      WebAccount *wrapper = WebAccount::Unwrap<WebAccount>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Id;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::WebAccount^>(info.This()))
      {
        return;
      }

      WebAccount *wrapper = WebAccount::Unwrap<WebAccount>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IMapView<::Platform::String^, ::Platform::String^>^ result = wrapper->_instance->Properties;
        info.GetReturnValue().Set(NodeRT::Collections::MapViewWrapper<::Platform::String^,::Platform::String^>::CreateMapViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));
            },
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
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
    ::Windows::Security::Credentials::WebAccount^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapWebAccount(::Windows::Security::Credentials::WebAccount^ wintRtInstance);
    friend ::Windows::Security::Credentials::WebAccount^ UnwrapWebAccount(Local<Value> value);
  };
  Persistent<FunctionTemplate> WebAccount::s_constructorTemplate;

  v8::Local<v8::Value> WrapWebAccount(::Windows::Security::Credentials::WebAccount^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(WebAccount::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Security::Credentials::WebAccount^ UnwrapWebAccount(Local<Value> value)
  {
     return WebAccount::Unwrap<WebAccount>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitWebAccount(Local<Object> exports)
  {
    WebAccount::Init(exports);
  }

  class IWebAccount : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IWebAccount").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("state").ToLocalChecked(), StateGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("userName").ToLocalChecked(), UserNameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("webAccountProvider").ToLocalChecked(), WebAccountProviderGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IWebAccount").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IWebAccount(::Windows::Security::Credentials::IWebAccount^ instance)
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
      
      ::Windows::Security::Credentials::IWebAccount^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::IWebAccount^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Security::Credentials::IWebAccount^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      IWebAccount *wrapperInstance = new IWebAccount(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::IWebAccount^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Security::Credentials::IWebAccount^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Security::Credentials::IWebAccount^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIWebAccount(winRtInstance));
    }


  



    static void StateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::IWebAccount^>(info.This()))
      {
        return;
      }

      IWebAccount *wrapper = IWebAccount::Unwrap<IWebAccount>(info.This());

      try 
      {
        ::Windows::Security::Credentials::WebAccountState result = wrapper->_instance->State;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UserNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::IWebAccount^>(info.This()))
      {
        return;
      }

      IWebAccount *wrapper = IWebAccount::Unwrap<IWebAccount>(info.This());

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
    
    static void WebAccountProviderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::IWebAccount^>(info.This()))
      {
        return;
      }

      IWebAccount *wrapper = IWebAccount::Unwrap<IWebAccount>(info.This());

      try 
      {
        ::Windows::Security::Credentials::WebAccountProvider^ result = wrapper->_instance->WebAccountProvider;
        info.GetReturnValue().Set(WrapWebAccountProvider(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Security::Credentials::IWebAccount^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIWebAccount(::Windows::Security::Credentials::IWebAccount^ wintRtInstance);
    friend ::Windows::Security::Credentials::IWebAccount^ UnwrapIWebAccount(Local<Value> value);
  };
  Persistent<FunctionTemplate> IWebAccount::s_constructorTemplate;

  v8::Local<v8::Value> WrapIWebAccount(::Windows::Security::Credentials::IWebAccount^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IWebAccount::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Security::Credentials::IWebAccount^ UnwrapIWebAccount(Local<Value> value)
  {
     return IWebAccount::Unwrap<IWebAccount>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIWebAccount(Local<Object> exports)
  {
    IWebAccount::Init(exports);
  }

  class PasswordCredential : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PasswordCredential").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "retrievePassword", RetrievePassword);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("userName").ToLocalChecked(), UserNameGetter, UserNameSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("resource").ToLocalChecked(), ResourceGetter, ResourceSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("password").ToLocalChecked(), PasswordGetter, PasswordSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("properties").ToLocalChecked(), PropertiesGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("PasswordCredential").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PasswordCredential(::Windows::Security::Credentials::PasswordCredential^ instance)
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
      
      ::Windows::Security::Credentials::PasswordCredential^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Security::Credentials::PasswordCredential^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsString()
        && info[2]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[1])));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[2])));
          
          winRtInstance = ref new ::Windows::Security::Credentials::PasswordCredential(arg0,arg1,arg2);
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
          winRtInstance = ref new ::Windows::Security::Credentials::PasswordCredential();
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

      PasswordCredential *wrapperInstance = new PasswordCredential(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Security::Credentials::PasswordCredential^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Security::Credentials::PasswordCredential^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPasswordCredential(winRtInstance));
    }


  
    static void RetrievePassword(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(info.This()))
      {
        return;
      }

      PasswordCredential *wrapper = PasswordCredential::Unwrap<PasswordCredential>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->RetrievePassword();
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



    static void UserNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(info.This()))
      {
        return;
      }

      PasswordCredential *wrapper = PasswordCredential::Unwrap<PasswordCredential>(info.This());

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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(info.This()))
      {
        return;
      }

      PasswordCredential *wrapper = PasswordCredential::Unwrap<PasswordCredential>(info.This());

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
    
    static void ResourceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(info.This()))
      {
        return;
      }

      PasswordCredential *wrapper = PasswordCredential::Unwrap<PasswordCredential>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Resource;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ResourceSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(info.This()))
      {
        return;
      }

      PasswordCredential *wrapper = PasswordCredential::Unwrap<PasswordCredential>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Resource = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void PasswordGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(info.This()))
      {
        return;
      }

      PasswordCredential *wrapper = PasswordCredential::Unwrap<PasswordCredential>(info.This());

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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(info.This()))
      {
        return;
      }

      PasswordCredential *wrapper = PasswordCredential::Unwrap<PasswordCredential>(info.This());

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
    
    static void PropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(info.This()))
      {
        return;
      }

      PasswordCredential *wrapper = PasswordCredential::Unwrap<PasswordCredential>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IPropertySet^ result = wrapper->_instance->Properties;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IPropertySet", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Security::Credentials::PasswordCredential^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPasswordCredential(::Windows::Security::Credentials::PasswordCredential^ wintRtInstance);
    friend ::Windows::Security::Credentials::PasswordCredential^ UnwrapPasswordCredential(Local<Value> value);
  };
  Persistent<FunctionTemplate> PasswordCredential::s_constructorTemplate;

  v8::Local<v8::Value> WrapPasswordCredential(::Windows::Security::Credentials::PasswordCredential^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PasswordCredential::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Security::Credentials::PasswordCredential^ UnwrapPasswordCredential(Local<Value> value)
  {
     return PasswordCredential::Unwrap<PasswordCredential>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPasswordCredential(Local<Object> exports)
  {
    PasswordCredential::Init(exports);
  }

  class PasswordVault : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PasswordVault").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "add", Add);
      Nan::SetPrototypeMethod(localRef, "remove", Remove);
      Nan::SetPrototypeMethod(localRef, "retrieve", Retrieve);
      Nan::SetPrototypeMethod(localRef, "findAllByResource", FindAllByResource);
      Nan::SetPrototypeMethod(localRef, "findAllByUserName", FindAllByUserName);
      Nan::SetPrototypeMethod(localRef, "retrieveAll", RetrieveAll);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("PasswordVault").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PasswordVault(::Windows::Security::Credentials::PasswordVault^ instance)
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
      
      ::Windows::Security::Credentials::PasswordVault^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordVault^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Security::Credentials::PasswordVault^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          winRtInstance = ref new ::Windows::Security::Credentials::PasswordVault();
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

      PasswordVault *wrapperInstance = new PasswordVault(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordVault^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Security::Credentials::PasswordVault^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Security::Credentials::PasswordVault^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPasswordVault(winRtInstance));
    }


  
    static void Add(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordVault^>(info.This()))
      {
        return;
      }

      PasswordVault *wrapper = PasswordVault::Unwrap<PasswordVault>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(info[0]))
      {
        try
        {
          ::Windows::Security::Credentials::PasswordCredential^ arg0 = UnwrapPasswordCredential(info[0]);
          
          wrapper->_instance->Add(arg0);
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
    static void Remove(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordVault^>(info.This()))
      {
        return;
      }

      PasswordVault *wrapper = PasswordVault::Unwrap<PasswordVault>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(info[0]))
      {
        try
        {
          ::Windows::Security::Credentials::PasswordCredential^ arg0 = UnwrapPasswordCredential(info[0]);
          
          wrapper->_instance->Remove(arg0);
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
    static void Retrieve(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordVault^>(info.This()))
      {
        return;
      }

      PasswordVault *wrapper = PasswordVault::Unwrap<PasswordVault>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && info[1]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[1])));
          
          ::Windows::Security::Credentials::PasswordCredential^ result;
          result = wrapper->_instance->Retrieve(arg0, arg1);
          info.GetReturnValue().Set(WrapPasswordCredential(result));
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
    static void FindAllByResource(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordVault^>(info.This()))
      {
        return;
      }

      PasswordVault *wrapper = PasswordVault::Unwrap<PasswordVault>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::Foundation::Collections::IVectorView<::Windows::Security::Credentials::PasswordCredential^>^ result;
          result = wrapper->_instance->FindAllByResource(arg0);
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Security::Credentials::PasswordCredential^>::CreateVectorViewWrapper(result, 
            [](::Windows::Security::Credentials::PasswordCredential^ val) -> Local<Value> {
              return WrapPasswordCredential(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(value);
            },
            [](Local<Value> value) -> ::Windows::Security::Credentials::PasswordCredential^ {
              return UnwrapPasswordCredential(value);
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
    static void FindAllByUserName(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordVault^>(info.This()))
      {
        return;
      }

      PasswordVault *wrapper = PasswordVault::Unwrap<PasswordVault>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::Foundation::Collections::IVectorView<::Windows::Security::Credentials::PasswordCredential^>^ result;
          result = wrapper->_instance->FindAllByUserName(arg0);
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Security::Credentials::PasswordCredential^>::CreateVectorViewWrapper(result, 
            [](::Windows::Security::Credentials::PasswordCredential^ val) -> Local<Value> {
              return WrapPasswordCredential(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(value);
            },
            [](Local<Value> value) -> ::Windows::Security::Credentials::PasswordCredential^ {
              return UnwrapPasswordCredential(value);
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
    static void RetrieveAll(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordVault^>(info.This()))
      {
        return;
      }

      PasswordVault *wrapper = PasswordVault::Unwrap<PasswordVault>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::Security::Credentials::PasswordCredential^>^ result;
          result = wrapper->_instance->RetrieveAll();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Security::Credentials::PasswordCredential^>::CreateVectorViewWrapper(result, 
            [](::Windows::Security::Credentials::PasswordCredential^ val) -> Local<Value> {
              return WrapPasswordCredential(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredential^>(value);
            },
            [](Local<Value> value) -> ::Windows::Security::Credentials::PasswordCredential^ {
              return UnwrapPasswordCredential(value);
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





  private:
    ::Windows::Security::Credentials::PasswordVault^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPasswordVault(::Windows::Security::Credentials::PasswordVault^ wintRtInstance);
    friend ::Windows::Security::Credentials::PasswordVault^ UnwrapPasswordVault(Local<Value> value);
  };
  Persistent<FunctionTemplate> PasswordVault::s_constructorTemplate;

  v8::Local<v8::Value> WrapPasswordVault(::Windows::Security::Credentials::PasswordVault^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PasswordVault::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Security::Credentials::PasswordVault^ UnwrapPasswordVault(Local<Value> value)
  {
     return PasswordVault::Unwrap<PasswordVault>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPasswordVault(Local<Object> exports)
  {
    PasswordVault::Init(exports);
  }

  class PasswordCredentialPropertyStore : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PasswordCredentialPropertyStore").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "lookup", Lookup);
      Nan::SetPrototypeMethod(localRef, "hasKey", HasKey);
      Nan::SetPrototypeMethod(localRef, "getView", GetView);
      Nan::SetPrototypeMethod(localRef, "insert", Insert);
      Nan::SetPrototypeMethod(localRef, "remove", Remove);
      Nan::SetPrototypeMethod(localRef, "clear", Clear);
      Nan::SetPrototypeMethod(localRef, "first", First);
      
                  
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("PasswordCredentialPropertyStore").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PasswordCredentialPropertyStore(::Windows::Security::Credentials::PasswordCredentialPropertyStore^ instance)
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
      
      ::Windows::Security::Credentials::PasswordCredentialPropertyStore^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredentialPropertyStore^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Security::Credentials::PasswordCredentialPropertyStore^) NodeRT::Utils::GetObjectInstance(info[0]);
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
          winRtInstance = ref new ::Windows::Security::Credentials::PasswordCredentialPropertyStore();
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

      PasswordCredentialPropertyStore *wrapperInstance = new PasswordCredentialPropertyStore(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredentialPropertyStore^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::Security::Credentials::PasswordCredentialPropertyStore^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::Security::Credentials::PasswordCredentialPropertyStore^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPasswordCredentialPropertyStore(winRtInstance));
    }


  
    static void Lookup(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredentialPropertyStore^>(info.This()))
      {
        return;
      }

      PasswordCredentialPropertyStore *wrapper = PasswordCredentialPropertyStore::Unwrap<PasswordCredentialPropertyStore>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Platform::Object^ result;
          result = wrapper->_instance->Lookup(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
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
    static void HasKey(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredentialPropertyStore^>(info.This()))
      {
        return;
      }

      PasswordCredentialPropertyStore *wrapper = PasswordCredentialPropertyStore::Unwrap<PasswordCredentialPropertyStore>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          bool result;
          result = wrapper->_instance->HasKey(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
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
    static void GetView(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredentialPropertyStore^>(info.This()))
      {
        return;
      }

      PasswordCredentialPropertyStore *wrapper = PasswordCredentialPropertyStore::Unwrap<PasswordCredentialPropertyStore>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IMapView<::Platform::String^, ::Platform::Object^>^ result;
          result = wrapper->_instance->GetView();
          info.GetReturnValue().Set(NodeRT::Collections::MapViewWrapper<::Platform::String^,::Platform::Object^>::CreateMapViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));
            },
            [](::Platform::Object^ val) -> Local<Value> {
              return CreateOpaqueWrapper(val);
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
    static void Insert(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredentialPropertyStore^>(info.This()))
      {
        return;
      }

      PasswordCredentialPropertyStore *wrapper = PasswordCredentialPropertyStore::Unwrap<PasswordCredentialPropertyStore>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          bool result;
          result = wrapper->_instance->Insert(arg0, arg1);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
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
    static void Remove(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredentialPropertyStore^>(info.This()))
      {
        return;
      }

      PasswordCredentialPropertyStore *wrapper = PasswordCredentialPropertyStore::Unwrap<PasswordCredentialPropertyStore>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          wrapper->_instance->Remove(arg0);
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
    static void Clear(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredentialPropertyStore^>(info.This()))
      {
        return;
      }

      PasswordCredentialPropertyStore *wrapper = PasswordCredentialPropertyStore::Unwrap<PasswordCredentialPropertyStore>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Clear();
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
    static void First(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredentialPropertyStore^>(info.This()))
      {
        return;
      }

      PasswordCredentialPropertyStore *wrapper = PasswordCredentialPropertyStore::Unwrap<PasswordCredentialPropertyStore>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IIterator<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Platform::Object^>^>^ result;
          result = wrapper->_instance->First();
          info.GetReturnValue().Set(NodeRT::Collections::IteratorWrapper<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Platform::Object^>^>::CreateIteratorWrapper(result, 
            [](::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Platform::Object^>^ val) -> Local<Value> {
              return NodeRT::Collections::KeyValuePairWrapper<::Platform::String^,::Platform::Object^>::CreateKeyValuePairWrapper(val, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](::Platform::Object^ val) -> Local<Value> {
              return CreateOpaqueWrapper(val);
            }
          );
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
      if (NodeRT::Utils::CaseInsenstiveEquals(L"mapChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredentialPropertyStore^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        PasswordCredentialPropertyStore *wrapper = PasswordCredentialPropertyStore::Unwrap<PasswordCredentialPropertyStore>(info.This());
      
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

          registrationToken = wrapper->_instance->MapChanged::add(
            ref new ::Windows::Foundation::Collections::MapChangedEventHandler<::Platform::String^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Foundation::Collections::IObservableMap<::Platform::String^, ::Platform::Object^>^ arg0, ::Windows::Foundation::Collections::IMapChangedEventArgs<::Platform::String^>^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
           	    HandleScope scope;
                TryCatch tryCatch;
              
                Local<Value> error;

                Local<Value> wrappedArg0 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IObservableMap`2", arg0);
                Local<Value> wrappedArg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IMapChangedEventArgs`1", arg1);

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

      if ((NodeRT::Utils::CaseInsenstiveEquals(L"mapChanged", str)))
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"mapChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Security::Credentials::PasswordCredentialPropertyStore^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          PasswordCredentialPropertyStore *wrapper = PasswordCredentialPropertyStore::Unwrap<PasswordCredentialPropertyStore>(info.This());
          wrapper->_instance->MapChanged::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Security::Credentials::PasswordCredentialPropertyStore^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPasswordCredentialPropertyStore(::Windows::Security::Credentials::PasswordCredentialPropertyStore^ wintRtInstance);
    friend ::Windows::Security::Credentials::PasswordCredentialPropertyStore^ UnwrapPasswordCredentialPropertyStore(Local<Value> value);
  };
  Persistent<FunctionTemplate> PasswordCredentialPropertyStore::s_constructorTemplate;

  v8::Local<v8::Value> WrapPasswordCredentialPropertyStore(::Windows::Security::Credentials::PasswordCredentialPropertyStore^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PasswordCredentialPropertyStore::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Security::Credentials::PasswordCredentialPropertyStore^ UnwrapPasswordCredentialPropertyStore(Local<Value> value)
  {
     return PasswordCredentialPropertyStore::Unwrap<PasswordCredentialPropertyStore>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPasswordCredentialPropertyStore(Local<Object> exports)
  {
    PasswordCredentialPropertyStore::Init(exports);
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
  
  NodeRT::Windows::Security::Credentials::InitKeyCredentialStatusEnum(target);
  NodeRT::Windows::Security::Credentials::InitKeyCredentialAttestationStatusEnum(target);
  NodeRT::Windows::Security::Credentials::InitKeyCredentialCreationOptionEnum(target);
  NodeRT::Windows::Security::Credentials::InitWebAccountStateEnum(target);
  NodeRT::Windows::Security::Credentials::InitWebAccountPictureSizeEnum(target);
  NodeRT::Windows::Security::Credentials::InitKeyCredentialRetrievalResult(target);
  NodeRT::Windows::Security::Credentials::InitKeyCredentialOperationResult(target);
  NodeRT::Windows::Security::Credentials::InitKeyCredentialAttestationResult(target);
  NodeRT::Windows::Security::Credentials::InitKeyCredential(target);
  NodeRT::Windows::Security::Credentials::InitKeyCredentialManager(target);
  NodeRT::Windows::Security::Credentials::InitWebAccountProvider(target);
  NodeRT::Windows::Security::Credentials::InitWebAccount(target);
  NodeRT::Windows::Security::Credentials::InitIWebAccount(target);
  NodeRT::Windows::Security::Credentials::InitPasswordCredential(target);
  NodeRT::Windows::Security::Credentials::InitPasswordVault(target);
  NodeRT::Windows::Security::Credentials::InitPasswordCredentialPropertyStore(target);

  NodeRT::Utils::RegisterNameSpace("Windows.Security.Credentials", target);
}


NODE_MODULE(binding, init)
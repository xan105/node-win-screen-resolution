/*
Copyright (c) Anthony Beaumont
This source code is licensed under the MIT License
found in the LICENSE file in the root directory of this source tree.
*/

/* NOTE: Your project need to include MFC either statically or dynamically.
You will also need to have afxtempl.h in your precompiled header. */
#include "pch.h"
#include "videomod.h"
#include "dpi.h"
#include <napi.h>
#pragma comment(lib, "user32.lib")

Napi::Array GetResolutionList(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  Napi::Array list = Napi::Array::New(env);

  CAvailableVideoModes modes;
  
	if (CVideoModes::GetAvailableVideoModes(modes))
	{
		for (int i = 0; i < modes.GetSize(); i++)
		{
				CVideoMode mode = modes.GetAt(i);
				
				Napi::Object resolution = Napi::Object::New(env);
				resolution.Set("width", mode.m_dwWidth);
				resolution.Set("height", mode.m_dwHeight);
				
        list.Set(uint32_t(i), resolution);
		}
	}
	
	return list;
}

Napi::Object GetCurrentResolution(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  Napi::Object resolution = Napi::Object::New(env);
  resolution.Set("width", GetSystemMetrics(SM_CXSCREEN));
	resolution.Set("height", GetSystemMetrics(SM_CYSCREEN));
	return resolution;
}

/* NAPI Initialize add-on*/

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  
  DpiAwareness();
  
  exports.Set("GetResolutionList", Napi::Function::New(env, GetResolutionList));
  exports.Set("GetCurrentResolution", Napi::Function::New(env, GetCurrentResolution));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
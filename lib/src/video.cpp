/*
Copyright (c) Anthony Beaumont
This source code is licensed under the MIT License
found in the LICENSE file in the root directory of this source tree.
*/

/* NOTE: Your project need to include MFC either statically or dynamically.
You will also need to have afxtempl.h in your precompiled header. */
#include "pch.h"
#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif
#include <winuser.h>
#include <napi.h>

Napi::Array GetAvailableDisplayMode(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  Napi::Array modes = Napi::Array::New(env);

  DEVMODE dm;
  DWORD iModeNum = 0;
  while (EnumDisplaySettings(NULL, iModeNum, &dm))
  {
    Napi::Object mode = Napi::Object::New(env);
    mode.Set("width", dm.dmPelsWidth);
    mode.Set("height", dm.dmPelsHeight);
    mode.Set("hz", dm.dmDisplayFrequency);
    mode.Set("color", dm.dmBitsPerPel);
    
    modes.Set(uint32_t(iModeNum), mode);
    ++iModeNum;
  }
  
  if (iModeNum == 0) Napi::Error::New(env, "Failed to enumerate display settings").ThrowAsJavaScriptException();
  
  return modes;
}

Napi::Object GetCurrentDisplayMode(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
	
  HDC hdc = ::GetDC(NULL);
  if (hdc == NULL) Napi::Error::New(env, "Failed to get current display settings").ThrowAsJavaScriptException();
  
  Napi::Object mode = Napi::Object::New(env);
  mode.Set("width", GetDeviceCaps(hdc, HORZRES));
  mode.Set("height", GetDeviceCaps(hdc, VERTRES));
  mode.Set("hz", GetDeviceCaps(hdc, VREFRESH));
  mode.Set("color", GetDeviceCaps(hdc, BITSPIXEL));
	
  ::ReleaseDC(NULL, hdc);

  return mode;
}

/* NAPI Initialize add-on*/

Napi::Object Init(Napi::Env env, Napi::Object exports) {
	
  SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE); //>=Win10
	
  exports.Set("getAvailableDisplayMode", Napi::Function::New(env, GetAvailableDisplayMode));
  exports.Set("getCurrentDisplayMode", Napi::Function::New(env, GetCurrentDisplayMode));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
/*
Copyright (c) Anthony Beaumont
This source code is licensed under the MIT License
found in the LICENSE file in the root directory of this source tree.
*/

#include "video.h"
#include "display.h"

Napi::Array GetAvailableDisplayMode(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  Napi::Array modes = Napi::Array::New(env);

  DEVMODEW dm = {};
  DWORD iModeNum = 0;
  while (EnumDisplaySettingsW(NULL, iModeNum, &dm))
  {
    Napi::Object mode = Napi::Object::New(env);
    mode.Set("width", dm.dmPelsWidth);
    mode.Set("height", dm.dmPelsHeight);
    mode.Set("hz", dm.dmDisplayFrequency);
    mode.Set("color", dm.dmBitsPerPel);
    
    modes.Set(uint32_t(iModeNum), mode);
    ++iModeNum;
  }

  return modes;
}

Napi::Object GetCurrentDisplayMode(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  Napi::Object mode = Napi::Object::New(env);
  
  HDC hdc = ::GetDC(NULL);
  if (hdc == NULL) { 
    return mode;
  }
  
  mode.Set("width", GetDeviceCaps(hdc, HORZRES));
  mode.Set("height", GetDeviceCaps(hdc, VERTRES));
  mode.Set("hz", GetDeviceCaps(hdc, VREFRESH));
  mode.Set("color", GetDeviceCaps(hdc, BITSPIXEL));

  double scale = (GetDpiForSystem() / 96.0) * 100.0;
  mode.Set("dpi", static_cast<int>(scale));

  ::ReleaseDC(NULL, hdc);

  return mode;
}

/* NAPI Initialize add-on*/

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  
  SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE); //>=Win10
  exports.Set("getAvailableDisplayMode", Napi::Function::New(env, GetAvailableDisplayMode));
  exports.Set("getCurrentDisplayMode", Napi::Function::New(env, GetCurrentDisplayMode));
  
  exports.Set("getActiveDisplays", Napi::Function::New(env, GetActiveDisplays));
  exports.Set("changePrimaryDisplay", Napi::Function::New(env, ChangePrimaryDisplay));
  
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
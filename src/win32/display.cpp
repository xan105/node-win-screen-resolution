/*
Copyright (c) Anthony Beaumont
This source code is licensed under the MIT License
found in the LICENSE file in the root directory of this source tree.
*/

#include "display.h"

void ListDisplays(std::vector<Display>& displays) {
    
    DISPLAY_DEVICEW displayDevice = {};
    displayDevice.cb = sizeof(DISPLAY_DEVICEW);
    int deviceIndex = 0;

    while (EnumDisplayDevicesW(NULL, deviceIndex, &displayDevice, 0)) {
        if (displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) {
            Display display = {};
            
            display.name = displayDevice.DeviceName;
            display.adapter = displayDevice.DeviceString;
            display.primary = displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE;

            // Now query for the first monitor associated with this adapter
            DISPLAY_DEVICEW monitorDevice = {};
            monitorDevice.cb = sizeof(DISPLAY_DEVICEW);
            DWORD monitorIndex = 0;
            if (EnumDisplayDevicesW(displayDevice.DeviceName, monitorIndex, &monitorDevice, 0)) {
                display.monitor = monitorDevice.DeviceString;
            }

            // Get the display settings
            ZeroMemory(&display.devMode, sizeof(display.devMode));
            display.devMode.dmSize = sizeof(display.devMode);
            if (EnumDisplaySettingsW(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &display.devMode)) { 
                Dpi dpi = { 96, 96 }; // Default DPI
                
                //Get handle from offset
                POINT offset = { display.devMode.dmPosition.x, display.devMode.dmPosition.y };
                HMONITOR hMonitor = MonitorFromPoint(offset, MONITOR_DEFAULTTONEAREST);
                
                MONITORINFOEXW monitorInfo = {};
                monitorInfo.cbSize = sizeof(monitorInfo);
                if (GetMonitorInfoW(hMonitor, &monitorInfo)) {
                  if (monitorInfo.szDevice == display.name){ //Make sure it's the correct handle
                    //Get DPI
                    GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &dpi.x, &dpi.y);
                  } 
                }
                display.dpi = dpi;
            } else {
              continue;
            }
            
            displays.push_back(display);
        }
        deviceIndex++;
    }
}

int UpdateVirtualScreen(int displayIndex, std::vector<Display>& displays) {

    POINT offset = {
        displays[displayIndex].devMode.dmPosition.x,
        displays[displayIndex].devMode.dmPosition.y
    };

    for (auto display = displays.begin(); display != displays.end(); ++display) {
        auto index = std::distance(displays.begin(), display);
        
        // We want to change the position
        DWORD flags = CDS_UPDATEREGISTRY | CDS_NORESET;
        display->devMode.dmFields |= DM_POSITION;

        // Set the position of the display
        if (index == displayIndex) {
            flags |= CDS_SET_PRIMARY;
            display->devMode.dmPosition.x = 0;
            display->devMode.dmPosition.y = 0;
        } else {
            display->devMode.dmPosition.x -= offset.x;
            display->devMode.dmPosition.y -= offset.y;
        }

        // Change the display settings
        if (ChangeDisplaySettingsExW(display->name.c_str(), &display->devMode, NULL, flags, NULL) != DISP_CHANGE_SUCCESSFUL) {
            return GetLastError();
        }
    }

    // Commit the changes
    if (ChangeDisplaySettingsExW(NULL, NULL, NULL, 0, NULL) != DISP_CHANGE_SUCCESSFUL) {
        return GetLastError();
    }

    return 0;
}

Napi::Array GetActiveDisplays(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  Napi::Array activeDisplays = Napi::Array::New(env);

  std::vector<Display> displays;
  ListDisplays(displays);
  
  for (auto display = displays.begin(); display != displays.end(); ++display) {
    auto index = std::distance(displays.begin(), display);

    Napi::Object offset = Napi::Object::New(env);
    offset.Set("x", display->devMode.dmPosition.x);
    offset.Set("y", display->devMode.dmPosition.y);
    
    Napi::Object activeDisplay = Napi::Object::New(env);
    activeDisplay.Set("id", toString(display->name));
    activeDisplay.Set("adapter", toString(display->adapter));
    activeDisplay.Set("monitor", toString(display->monitor));
    activeDisplay.Set("primary", display->primary);
    activeDisplay.Set("width", display->devMode.dmPelsWidth);
    activeDisplay.Set("height", display->devMode.dmPelsHeight);
    activeDisplay.Set("hz", display->devMode.dmDisplayFrequency);
    
    if(display->dpi.x == display->dpi.y){ //NB: Microsoft states that dpiX == dpiY and just to pick one
      activeDisplay.Set("scale", static_cast<UINT>((display->dpi.x / 96.0) * 100.0));
    } else { //But better safe than sorry
      Napi::Object scale = Napi::Object::New(env);
      scale.Set("x", static_cast<UINT>((display->dpi.x / 96.0) * 100.0));
      scale.Set("y", static_cast<UINT>((display->dpi.y / 96.0) * 100.0));
      activeDisplay.Set("scale", scale);
    }
    
    activeDisplay.Set("offset", offset);
    
    activeDisplays.Set(uint32_t(index), activeDisplay);
  }

  return activeDisplays;
}

Napi::Value ChangePrimaryDisplay(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  
  if (info.Length() != 1) {
    Napi::TypeError::New(env, "Expected 1 argument: TARGET DISPLAY").ThrowAsJavaScriptException();
    return env.Undefined();
  }
  
  if (!(info[0].IsString() || info[0].IsNumber())) {
    Napi::TypeError::New(env, "Expected string|number (TARGET DISPLAY)").ThrowAsJavaScriptException();
    return env.Undefined();
  }
  
  std::vector<Display> displays;
  ListDisplays(displays);
  
  int targetIndex = -1;
  if(info[0].IsString()){
    std::wstring targetDisplay = toWString(info[0].As<Napi::String>().Utf8Value());
    for (auto display = displays.begin(); display != displays.end(); ++display) {
        auto index = std::distance(displays.begin(), display);
        
        if (display->name == targetDisplay){
          targetIndex = index;
          break;
        }
    }
  } else if (info[0].IsNumber()){
    targetIndex = info[0].As<Napi::Number>().Int32Value();
  }
  
  if (targetIndex < 0 || targetIndex >= (int)displays.size()) {
    Napi::TypeError::New(env, "Target display not found !").ThrowAsJavaScriptException();
    return env.Undefined();
  }
  
  int code = UpdateVirtualScreen(targetIndex, displays);
  return Napi::Number::New(env, code);
}
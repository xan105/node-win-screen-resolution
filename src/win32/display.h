/*
Copyright (c) Anthony Beaumont
This source code is licensed under the MIT License
found in the LICENSE file in the root directory of this source tree.
*/

#define WIN32_LEAN_AND_MEAN

#include <napi.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include "string.h"

#include <shellscalingapi.h>

struct Dpi {
  UINT x;
  UINT y;
};

struct Display {
    std::wstring name;
    std::wstring adapter;
    std::wstring monitor;
    bool primary;
    DEVMODEW devMode;
    Dpi dpi;
};

void ListDisplays(std::vector<Display>& displays);
int UpdateVirtualScreen(int displayIndex, std::vector<Display>& displays);
Napi::Array GetActiveDisplays(const Napi::CallbackInfo& info);
Napi::Value ChangePrimaryDisplay(const Napi::CallbackInfo& info);
/*
Copyright (c) Anthony Beaumont
This source code is licensed under the MIT License
found in the LICENSE file in the root directory of this source tree.
*/

#define WIN32_LEAN_AND_MEAN

#include <napi.h>
#include <windows.h>

#include <shellscalingapi.h>

Napi::Array GetAvailableDisplayMode(const Napi::CallbackInfo& info);
Napi::Object GetCurrentDisplayMode(const Napi::CallbackInfo& info);
Napi::Object Init(Napi::Env env, Napi::Object exports);
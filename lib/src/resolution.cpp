/*
MIT License

Copyright (c) Anthony Beaumont

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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
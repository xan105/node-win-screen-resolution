/*
Copyright (c) Anthony Beaumont
This source code is licensed under the MIT License
found in the LICENSE file in the root directory of this source tree.
*/

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>

std::wstring toWString(const std::string& s);
int toInt(size_t val);
std::string toString(const std::wstring& s);
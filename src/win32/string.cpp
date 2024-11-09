/*
Copyright (c) Anthony Beaumont
This source code is licensed under the MIT License
found in the LICENSE file in the root directory of this source tree.
*/

#include "string.h"

std::wstring toWString(const std::string& s) {
    int size = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.length(), nullptr, 0);
    std::wstring buf(size, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.length(), &buf[0], size);
    return buf;
}

int toInt(size_t val) { //64bits
    return (val <= INT_MAX) ? (int)((size_t)val) : 0;
}

std::string toString(const std::wstring& s) {
    int size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, s.c_str(), toInt(s.length()), NULL, 0, NULL, NULL);
    std::string buf = std::string(size, '\0');
    WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, s.c_str(), toInt(s.length()), &buf[0], size, NULL, NULL);
    return buf;
}
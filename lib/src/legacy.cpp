/*
Copyright (c) Anthony Beaumont
This source code is licensed under the MIT License
found in the LICENSE file in the root directory of this source tree.
*/

#include "pch.h"
#include <winuser.h>

void DpiAwareness(){
  // Windows Vista, 7, 8, 8.1
  SetProcessDPIAware();
}
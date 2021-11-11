#include "..\pch.h"
#include <winuser.h>

void DpiAwareness(){
  // Windows Vista, 7, 8, 8.1
  SetProcessDPIAware();
}
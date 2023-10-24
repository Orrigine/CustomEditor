#pragma once

#ifndef WIN32
#include <windows.h>
#endif

#define MAX_NAME_STRING 256
#define HInstance() GetModuleHandle(NULL)
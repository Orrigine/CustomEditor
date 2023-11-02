#pragma once
#include "Common/Headers/d3dApp.h"
#include "Common/Headers/MathHelper.h"
#include "Common/Headers/UploadBuffer.h"

#ifndef WIN32
#include <windows.h>
#include <windowsx.h>
#endif

#define MAX_NAME_STRING 256
#define HInstance() GetModuleHandle(NULL)

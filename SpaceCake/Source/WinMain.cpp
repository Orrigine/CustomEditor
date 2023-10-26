#include "Headers/pch.h"
#include <iostream>
using namespace std;
#pragma region Global Variables

WCHAR WindowClass[MAX_NAME_STRING] = L"WinClass";
WCHAR WindowTitle[MAX_NAME_STRING] = L"MY EFFING WINDOW";

INT WindowHeight;
INT WindowWidth;

BOOL WindowShouldClose;

HICON WindowIcon;
#pragma endregion

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
    PSTR cmdLine, int showCmd)
{
    return 0;
}
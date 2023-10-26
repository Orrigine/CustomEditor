#include "pch.h"
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

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WindowShouldClose = false;
    switch (uMsg)
    {
        // FIXME: Don't kill process on close
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


int main(void)
{
    cout << "haha" << endl;
}
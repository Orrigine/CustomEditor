#include "pch.h"

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

#pragma region Pre-Declcarations

void InitializeVariables();
void CreateWindowClass();
void InitializeWindow();
void MessageLoop();

#pragma endregion

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{

    InitializeVariables();
    CreateWindowClass();
    InitializeWindow();
    MessageLoop();

    return 0;
}

#pragma region Functions

void InitializeVariables()
{

    WindowHeight = 720;
    WindowWidth = 1280;
}

void CreateWindowClass()
{
    WNDCLASSEX wcex = {0};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW; // Redraw on horizontal or vertical movement/adjustment
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;

    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);           // Load the arrow cursor
    wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); // Set the background color to white

    wcex.hIcon = WindowIcon;
    wcex.hIconSm = WindowIcon;

    wcex.lpszClassName = WindowClass;
    wcex.lpszMenuName = nullptr;

    wcex.hInstance = HInstance();

    wcex.lpfnWndProc = WindowProcess;

    RegisterClassEx(&wcex);
}

void InitializeWindow()
{
    HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                             WindowWidth, WindowHeight, nullptr, /*menu*/ nullptr, HInstance(), /*spec instruct*/ nullptr);

    if (!hWnd)
    {
        MessageBox(NULL, L"Call to CreateWindow failed!", L"Error", NULL);
        PostQuitMessage(0);
    }
    ShowWindow(hWnd, SW_SHOW);
}

void MessageLoop()
{
    MSG msg = {0};

    if (msg.message == WM_QUIT)
    {
        WindowShouldClose = true;
    }
    while (msg.message != WM_QUIT)
    {

        if (WindowShouldClose == true)
        {
            return;
        };
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg); // Translate virtual-key messages into character messages
            DispatchMessage(&msg);  // Send message to WindowProc
        }
    }
}

#pragma endregion

#include "../Headers/Render.h" 

Render::Window::Window(){}
Render::Window::~Window(){}

int CALLBACK Render::Window::WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{

    InitializeVariables();
    CreateWindowClass();
    InitializeWindow();
    MessageLoop();

    return 0;
}
private void  Render::Window::InitializeVariables(int width, int height)
{

    WindowHeight = height;
    WindowWidth = width;
}

private void Render::Window::CreateWindowClass()
{
    WNDCLASSEX wcex = { 0 };
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

private HWND  Render::Window::InitializeWindow(std::string name)
{
    HWND hWnd = CreateWindow(WindowClass, name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        WindowWidth, WindowHeight, nullptr, /*menu*/ nullptr, HInstance(), /*spec instruct*/ nullptr);

    if (!hWnd)
    {
        MessageBox(NULL, L"Call to CreateWindow failed!", L"Error", NULL);
        PostQuitMessage(0);
    }
    ShowWindow(hWnd, SW_SHOW);
    return hwnd;
}

private void  Render::Window::MessageLoop()
{
    MSG msg = { 0 };

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

public HWND CALLBACK Render::Window::CreateWindow(std::string name, int width, int height)
{
    HWND returnWindow;

    InitializeVariables();
    CreateWindowClass();
    returnWindow = InitializeWindow();
    MessageLoop();

    return returnWindow;
}
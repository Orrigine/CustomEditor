#include "Headers/SpaceEngine.h"
#include "Headers/Render.h"

WCHAR WindowClass[MAX_NAME_STRING] = L"SpaceEngineWindowClass";
std::shared_ptr<Render::Window> Render::Window::_instance = nullptr;

Render::Window::Window()
{

    _wcex = {};
    _instance = nullptr;
}
Render::Window::~Window() {}

LRESULT CALLBACK Render::Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    // use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
    if (msg == WM_NCCREATE)
    {
        // extract ptr to window class from creation data
        const CREATESTRUCTW *const pCreate = reinterpret_cast<CREATESTRUCTW *>(lParam);
        Window *const pWnd = static_cast<Window *>(pCreate->lpCreateParams);
        // set WinAPI-managed user data to store ptr to window instance
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        // set message proc to normal (non-setup) handler now that setup is finished
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Render::Window::HandleMsgThunk));
        // forward message to window instance handler
        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
    }
    // if we get a message before the WM_NCCREATE message, handle with default handler
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Render::Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    // retrieve ptr to window instance
    Window *const pWnd = reinterpret_cast<Window *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    // forward message to window instance handler
    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Render::Window::HandleMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{

    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

        // we don't want the DefProc to handle this message because
        // we want our destructor to destroy the window, so return 0 instead of break
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
        return 0;
        // clear keystate when window loses focus to prevent input getting "stuck"
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
        return 0;
    }
}

void Render::Window::InitializeVariables(int width, int height)
{

    _windowHeight = height;
    _windowWidth = width;
}

// void Render::Window::CreateWindowClass()
// {
// 	_wcex.cbSize = sizeof(WNDCLASSEX);
// 	_wcex.style = CS_HREDRAW | CS_VREDRAW; // Redraw on horizontal or vertical movement/adjustment
// 	_wcex.lpfnWndProc = Render::Window::HandleMsgSetup;
// 	_wcex.cbClsExtra = 0;
// 	_wcex.cbWndExtra = 0;

// 	_wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);           // Load the arrow cursor
// 	_wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); // Set the background color to white

// 	_wcex.lpszClassName = WindowClass;
// 	_wcex.lpszMenuName = nullptr;

// 	_wcex.hInstance = HInstance();
// 	RegisterClassEx(&_wcex);
// }

HWND Render::Window::InitializeWindow(LPCWSTR name)
{
    HWND hWnd = CreateWindow(WindowClass, name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                             _windowWidth, _windowHeight, nullptr, /*menu*/ nullptr, HInstance(), /*spec instruct*/ nullptr);

    if (!hWnd)
    {
        MessageBox(NULL, L"Call to CreateWindow failed!", L"Error", NULL);
        PostQuitMessage(0);
    }
    ShowWindow(hWnd, SW_SHOW);
    return hWnd;
}

void Render::Window::MessageLoop()
{

    MSG msg = {0};

    if (msg.message == WM_QUIT)
    {
        _windowShouldClose = true;
    }
    while (msg.message != WM_QUIT)
    {

        if (_windowShouldClose == true)
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

HWND CALLBACK Render::Window::CreateGameWindow(LPCWSTR name, int width, int height)
{

    HWND returnWindow;

    InitializeVariables(width, height);
    CreateWindowClass();
    returnWindow = InitializeWindow(name);
    MessageLoop();

    return returnWindow;
}

std::shared_ptr<Render::Window> Render::Window::GetInstance()
{

    if (_instance == nullptr)
    {
        std::shared_ptr<Render::Window> ptr(new Render::Window);
        _instance = ptr;
    }
    return _instance;
}
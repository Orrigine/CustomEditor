#pragma once


#include "Common/Headers/d3dApp.h"
#include "Common/Headers/MathHelper.h"
#include "Common/Headers/UploadBuffer.h"
#include <memory.h>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Gdi32.lib")

namespace Render
{
	class Window
	{
    private:

        static std::shared_ptr<Render::Window> _instance;
        
        int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT);

        static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

        void InitializeVariables(int, int);
        void CreateWindowClass();
        HWND InitializeWindow(LPCWSTR);
        void MessageLoop();
        WNDCLASSEX _wcex;
       
        bool _windowShouldClose;
        int _windowWidth;
        int _windowHeight;
    public:
        Window();
        ~Window();
        static std::shared_ptr<Render::Window> GetInstance();
        HWND CALLBACK CreateGameWindow(LPCWSTR, int, int);

     
	};
}
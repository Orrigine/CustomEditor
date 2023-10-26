
#include "Common/Headers/d3dApp.h"
#include "Common/Headers/MathHelper.h"
#include "Common/Headers/UploadBuffer.h"

namespace Render
{
	class Window
	{
    private:

        LRESULT CALLBACK WindowProcess(HWND, UINT, WPARAM, LPARAM);
        int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT);
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

        HWND CALLBACK CreateGameWindow(LPCWSTR, int, int);


     
	};
}

namespace Render
{
	class Window
	{
    private:
        int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT);
        void InitializeVariables(int, int);
        void CreateWindowClass();
        HWND InitializeWindow(std::string;);
        void MessageLoop();
    public:
        Window();
        ~Window();

        HWND CreateWindow(std::string, int, int);


     
	};
}
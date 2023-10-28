#include "Headers/pch.h"

using namespace std;
#pragma region Global Variables

#pragma endregion

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{

    Render::Window::GetInstance()->CreateGameWindow(L"HAHA", 50, 50);
	if (Engine::Keyboard::GetInstance()->KeyDown(Engine::Keyboard::Key::A))
	{
		Render::Window::GetInstance()->CreateGameWindow(L"HUHU", 450, 50);
	}
}
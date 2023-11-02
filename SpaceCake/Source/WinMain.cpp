#include "Headers/pch.h"

using namespace std;
#pragma region Global Variables

#pragma endregion

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
  Render::Window::GetInstance()->CreateGameWindow(L"HAHA", 1920, 500);
}
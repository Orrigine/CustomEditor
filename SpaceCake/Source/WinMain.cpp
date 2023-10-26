#include "Headers/pch.h"
#include "Headers/Render.h"
#include <iostream>
using namespace std;
#pragma region Global Variables

#pragma endregion

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{

    Render::Window::GetInstance()->CreateGameWindow(L"HAHA", 50, 50);
}
#include "Headers/pch.h"
#include "Graphics.h"
#include "Engine/Engine.h"
#include <iostream>
#include "Engine.h"

#pragma region Global Variables
#pragma endregion

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
                   PSTR cmdLine, int showCmd)
{
    SpaceEngine::Core core(hInstance);
    core.createWindow(800, 600, L"SpaceCake");
    core.init();
    core.run();
    // Window::GetInstance()->CreateGameWindow(L"SpaceEngine", 1080, 720);
    // Render::Window::GetInstance()->InitializeVariables(1080, 720);
    /*
    
    try
    {
        Window Application(hInstance);
        if (!Application.Initialize())
            return 0;
        else
            return Application.Run();
    }
    catch (DxException &e)
    {
        MessageBox(nullptr, e.ToString().c_str(), L"Engine Failed Init", MB_OK);
        return 0;
    }*/
}
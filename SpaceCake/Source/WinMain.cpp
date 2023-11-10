#include "Headers/pch.h"
#include "Graphics.h"
#include <iostream>
#include "Engine.h"

#include "Headers/Game.h"

#pragma region Global Variables
#pragma endregion

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
                   PSTR cmdLine, int showCmd)
{
    SpaceEngine::Engine engine(hInstance);
    Game game = Game(engine);
    game.init();
    // check if current state is Mainemenu

     //if (game._stateMachine->getCurrentState() == StateMainMenu::getInstance())
    game.run();
}
#include "Headers/Game.h"
//#include "Game.h"

// pass the engine to the game via constructor
std::shared_ptr<Game> Game::_instance = nullptr;
Game::Game(SpaceEngine::Engine engine) :_engine (engine)
{
 
}

Game::~Game()
{
}

void Game::run()
{

    _engine.createWindow(1280, 720, L"SpaceCake");
    _engine.init();
    _engine.run();
}

std::shared_ptr<Game> Game::GetInstance()
{

    if (_instance == nullptr)
    {
        _instance = std::shared_ptr<Game>(new Game(HInstance()));
    }
    return _instance;
}

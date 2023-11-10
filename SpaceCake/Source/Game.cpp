#include "Headers/Game.h"
// #include "Engine.h"
// #include "Engine/Core/Core.h"
// #include "Game.h"

std::shared_ptr<Game> Game::_instance = nullptr;

void myScript(void *engine, void *renderApp)
{
    Render::Window *render = (Render::Window *)renderApp;
    SpaceEngine::Engine *myEngine = (SpaceEngine::Engine *)engine;
    static float ftime = 0;

    if (render->getTotalTime() - ftime >= 4)
    {
        std::shared_ptr<SpaceEngine::Entity> entity = myEngine->createEntity("1");
        std::shared_ptr<SpaceEngine::SphereMesh> sphereMesh = entity->addComponent<SpaceEngine::SphereMesh>();

        ftime = render->getTotalTime();
    }
}

Game::Game(SpaceEngine::Engine engine) : _engine(engine)
{
}

Game::~Game()
{
}

void Game::init()
{

    // Set initial values
    _isRunning = true;
    _engine.createWindow(1920, 1080, L"SpaceCake");

    _stateMachine = new StateMachine();

    _engine.init();

    std::shared_ptr<SpaceEngine::Entity> cube_1 = _engine.createEntity("cube1");
    std::shared_ptr<SpaceEngine::Entity> cube_2 = _engine.createEntity("cube2");
    std::shared_ptr<SpaceEngine::Entity> obj = _engine.createEntity("obj");
    std::shared_ptr<SpaceEngine::Entity> empty = _engine.createEntity("empty");
    std::shared_ptr<SpaceEngine::Script> scriptFemiTest = empty->addComponent<SpaceEngine::Script>();

    scriptFemiTest->setScript(myScript);
    std::shared_ptr<SpaceEngine::Transform> cube1Transform = cube_1->getComponent<SpaceEngine::Transform>();
    std::shared_ptr<SpaceEngine::Transform> cube2Transform = cube_2->getComponent<SpaceEngine::Transform>();
    std::shared_ptr<SpaceEngine::Transform> objTransform = obj->getComponent<SpaceEngine::Transform>();
    std::shared_ptr<SpaceEngine::BoxMesh> cube1Mesh = cube_1->addComponent<SpaceEngine::BoxMesh>();
    std::shared_ptr<SpaceEngine::BoxMesh> cube2Mesh = cube_2->addComponent<SpaceEngine::BoxMesh>();
    std::shared_ptr<SpaceEngine::SphereMesh> sphereMesh = obj->addComponent<SpaceEngine::SphereMesh>();

    cube1Transform->setPosition({0, 1, 0});
    cube2Transform->setPosition({2, 0, 0});
    objTransform->setPosition({-2, 0, -1});

    cube1Transform->setScale({3, 3, 3});
    cube2Transform->setScale({2, 2, 2});
    objTransform->setScale({2, 2, 2});
}

void Game::run()
{
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

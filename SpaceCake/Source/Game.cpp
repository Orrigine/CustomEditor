#include "Headers/Game.h"
#include <math.h>

// pass the engine to the game via constructor
std::shared_ptr<Game> Game::_instance = nullptr;

void myScript(void* engine, void* renderApp)
{
    Render::Window* render = (Render::Window*)renderApp;
    SpaceEngine::Engine* myEngine = (SpaceEngine::Engine*)engine;
    static float ftime = 0;

    if (render->getTotalTime() - ftime >= 4)
    {
        std::shared_ptr<SpaceEngine::Entity> entity = myEngine->createEntity("1", "Planet");
        std::shared_ptr<SpaceEngine::SphereMesh> sphereMesh = entity->addComponent<SpaceEngine::SphereMesh>();
        std::shared_ptr<SpaceEngine::Transform> transform = entity->getComponent<SpaceEngine::Transform>();

        transform->setPosition({0, 5, 1});

        ftime = render->getTotalTime();
    }

    std::unordered_map<unsigned int, std::shared_ptr<SpaceEngine::Entity>> entities = myEngine->getEntities();
    /*for (auto elm = entities.begin(); elm != entities.end(); elm++) {
        if (elm->second->compareType("Planet")) {
            unsigned int entityId = elm->first;
            std::shared_ptr<SpaceEngine::Transform> transform = elm->second->getComponent<SpaceEngine::Transform>();

            SpaceEngine::Vector3f position = transform->getPosition();
            SpaceEngine::Vector3f rotation = transform->getRotation();
            SpaceEngine::Vector3f scale = transform->getScale();

            transform->setRotation({ rotation.x, /*rotation.y / 2.0f * render->getTotalTime(), rotation.z });
        }
    }*/

}

Game::Game(SpaceEngine::Engine engine) :_engine (engine)
{
 
}

Game::~Game()
{
}

void Game::createCrates(int nb)
{
    int x_p = 100;
    int y_p = 100;
    int array_crates[100][100] = { 0 };
    int compt = 0;
    int x = 0;
    int y = 0;

    float start_x = -10 , start_y = -10, x_tmp = -10, y_tmp = -10;
    float space = 10;

    for (; compt < nb; ) {
        x = rand() % x_p;
        y = rand() % y_p;

        if (array_crates[y][x] == 0) {
            compt++;
            array_crates[y][x] = 1;
        }
    }
    
    for (int i = 0, k = 1; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (array_crates[i][j] == 1) {
                std::shared_ptr<SpaceEngine::Entity> entity = _engine.createEntity(std::to_string(k), "Planet");
                std::shared_ptr<SpaceEngine::SphereMesh> sphereMesh = entity->addComponent<SpaceEngine::SphereMesh>();
                std::shared_ptr<SpaceEngine::Transform> transform = entity->getComponent<SpaceEngine::Transform>();
                int max = 100, min = 20;
                transform->setPosition({ powf ( -1, i) * (float)(x_tmp * space), powf(-1, j) * (float)(y_tmp * space),  (float)((rand() % (max - min + 1)) + min) });
              //  transform->setPosition({ (float)(x_tmp * space), 10,  100});
                float scale = rand() % 20;
                transform->setScale( { scale, scale, scale });
            }
            x_tmp += 0.1;
        }
        y_tmp += 0.1;
        x_tmp += start_x;
    }
}

void Game::run()
{
    srand(time(0));
    _engine.createWindow(1920, 1080, L"SpaceCake");
    _engine.init();

    createCrates(100);
    /*std::shared_ptr<SpaceEngine::Entity> cube_1 = _engine.createEntity("cube1");
    std::shared_ptr<SpaceEngine::Entity> cube_2 = _engine.createEntity("cube2");
    std::shared_ptr<SpaceEngine::Entity> obj = _engine.createEntity("obj", "Planet");*/
    std::shared_ptr<SpaceEngine::Entity> empty = _engine.createEntity("empty");
    std::shared_ptr<SpaceEngine::Script> scriptFemiTest = empty->addComponent<SpaceEngine::Script>();
    
    scriptFemiTest->setScript(myScript);
   /* std::shared_ptr<SpaceEngine::Transform> cube1Transform = cube_1->getComponent<SpaceEngine::Transform>();
    std::shared_ptr<SpaceEngine::Transform> cube2Transform = cube_2->getComponent<SpaceEngine::Transform>();
    std::shared_ptr<SpaceEngine::Transform> objTransform = obj->getComponent<SpaceEngine::Transform>();
    std::shared_ptr<SpaceEngine::BoxMesh> cube1Mesh = cube_1->addComponent<SpaceEngine::BoxMesh>();
    std::shared_ptr<SpaceEngine::BoxMesh> cube2Mesh = cube_2->addComponent<SpaceEngine::BoxMesh>();
    std::shared_ptr<SpaceEngine::SphereMesh> sphereMesh = obj->addComponent<SpaceEngine::SphereMesh>();*/

   /* cube1Transform->setPosition({0, 1, -2});
    cube2Transform->setPosition({ 2, -4, 0 });
    objTransform->setPosition({ -2, 0, -1 });*/

    /*cube1Transform->setScale({2, 2, 2});
    cube2Transform->setScale({ 2, 2, 2 });
    objTransform->setScale({ 2, 2, 2 });*/

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

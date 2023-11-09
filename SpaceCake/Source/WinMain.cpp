#include "Headers/pch.h"
#include "Graphics.h"
#include <iostream>
#include "Engine.h"

#pragma region Global Variables
#pragma endregion

void myScript(void* engine, void* renderApp)
{
    Render::Window* render = (Render::Window*)renderApp;
    SpaceEngine::Engine *myEngine = (SpaceEngine::Engine*) engine;
    static float ftime = 0;
    
    if ( render->getTotalTime() - ftime >= 4)  {
        std::shared_ptr<SpaceEngine::Entity> entity = myEngine->createEntity("1");
        std::shared_ptr<SpaceEngine::SphereMesh> sphereMesh = entity->addComponent<SpaceEngine::SphereMesh>();

        ftime = render->getTotalTime();
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
                   PSTR cmdLine, int showCmd)
{
    SpaceEngine::Engine engine(hInstance);

    engine.createWindow(1920, 1080, L"SpaceCake");

    std::shared_ptr<SpaceEngine::Entity> cube_1 = engine.createEntity("cube1");
    std::shared_ptr<SpaceEngine::Entity> cube_2 = engine.createEntity("cube2");
    std::shared_ptr<SpaceEngine::Entity> obj = engine.createEntity("obj");

    std::shared_ptr<SpaceEngine::Entity> empty = engine.createEntity("empty");
    std::shared_ptr<SpaceEngine::Script> scriptFemiTest = empty->addComponent<SpaceEngine::Script>();
    scriptFemiTest->setScript(myScript);
 
    std::shared_ptr<SpaceEngine::Transform> cube1Transform = cube_1->getComponent<SpaceEngine::Transform>();
    std::shared_ptr<SpaceEngine::Transform> cube2Transform = cube_2->getComponent<SpaceEngine::Transform>();
    std::shared_ptr<SpaceEngine::Transform> objTransform = obj->getComponent<SpaceEngine::Transform>();
    std::shared_ptr<SpaceEngine::BoxMesh> cube1Mesh = cube_1->addComponent<SpaceEngine::BoxMesh>();
    std::shared_ptr<SpaceEngine::BoxMesh> cube2Mesh = cube_2->addComponent<SpaceEngine::BoxMesh>();
    std::shared_ptr<SpaceEngine::SphereMesh> sphereMesh = obj->addComponent<SpaceEngine::SphereMesh>();

    cube1Transform->setPosition({ 0, 1, 0 });
    cube2Transform->setPosition({ 2, 0, 0 });
    objTransform->setPosition({ - 2 , 0 , -1});

    cube1Transform->setScale({ 3, 3, 3 });
    cube2Transform->setScale({ 2, 2, 2 });
    objTransform->setScale({ 2, 2, 2 });

    engine.init();
    engine.run();
}
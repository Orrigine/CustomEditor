#include "Headers/pch.h"
#include "Graphics.h"
#include <iostream>
#include "Engine.h"

#pragma region Global Variables
#pragma endregion

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
                   PSTR cmdLine, int showCmd)
{
    SpaceEngine::Core core(hInstance);
    std::shared_ptr<SpaceEngine::Scene> startScene = NULL;

    core.createWindow(800, 600, L"SpaceCake");
    startScene = core.createScene("start");
    core.setStartScene("start");

    std::shared_ptr<SpaceEngine::Entity> cube_1 = startScene->createEntity("cube1");
    std::shared_ptr<SpaceEngine::Entity> cube_2 = startScene->createEntity("cube2");
    std::shared_ptr<SpaceEngine::Entity> obj = startScene->createEntity("obj");

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

    core.init();
    core.run();
}
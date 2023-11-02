/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** SystemSetRotation
*/

#include "SystemSetRotation.hpp"

namespace SpaceEngine {
    void SystemSetRotation::init(std::unordered_map<std::string,
    std::shared_ptr<IComponentManager>> mapComponentManagers, 
    std::shared_ptr<Entity> entity, std::string component, va_list ptr)
    {
        if (component !=  "Rotation")
            return;
        std::shared_ptr<RotationManager> RotationManager(std::dynamic_pointer_cast<RotationManager>(mapComponentManagers["RotationManager"]));
        std::shared_ptr<Rotation> RotationComponent = std::dynamic_pointer_cast<Rotation>(RotationManager->getComponent(entity));
        if (RotationComponent == nullptr)
            return;
        float angleX = va_arg(ptr, float);
        float angleY = va_arg(ptr, float);
        float angleZ = va_arg(ptr, float);
        
        RotationComponent->setRotation(angleX, angleY, angleZ);
    }

    void SystemSetRotation::update(std::unordered_map<std::string, 
    std::shared_ptr<IComponentManager>> *mapComponentManger, 
    std::vector<std::shared_ptr<Entity>> *entities)
    {
    }

    SystemSetRotation::SystemSetRotation()
    {
    }

    SystemSetRotation::~SystemSetRotation()
    {
    }
}
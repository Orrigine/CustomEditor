/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** SystemSetScale
*/

#include "SystemSetScale.hpp"

namespace SpaceEngine {
    void SystemSetScale::init(std::unordered_map<std::string,
    std::shared_ptr<IComponentManager>> mapComponentManagers, 
    std::shared_ptr<Entity> entity, std::string component, va_list ptr)
    {
        if (component !=  "Scale")
            return;
        std::shared_ptr<ScaleManager> ScaleManager(std::dynamic_pointer_cast<ScaleManager>(mapComponentManagers["ScaleManager"]));
        std::shared_ptr<Scale> ScaleComponent = std::dynamic_pointer_cast<Scale>(ScaleManager->getComponent(entity));
        if (ScaleComponent == nullptr)
            return;
        float scaleX = va_arg(ptr, float);
        float scaleY = va_arg(ptr, float);
        float scaleZ = va_arg(ptr, float);
        
        ScaleComponent->setScale(scaleX, scaleY, scaleZ);
    }

    void SystemSetScale::update(std::unordered_map<std::string, 
    std::shared_ptr<IComponentManager>> *mapComponentManger, 
    std::vector<std::shared_ptr<Entity>> *entities)
    {
    }

    SystemSetScale::SystemSetScale()
    {
    }

    SystemSetScale::~SystemSetScale()
    {
    }
}
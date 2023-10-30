/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** SystemSetPosition
*/

#include "SystemSetPosition.hpp"

namespace SpaceEngine {
        void SystemSetPosition::init(std::unordered_map<std::string,
    std::shared_ptr<IComponentManager>> mapComponentManagers, 
    std::shared_ptr<Entity> entity, std::string component, va_list ptr)
    {
        if (component !=  "Position")
            return;
        std::shared_ptr<PositionManager> PositionManager(std::dynamic_pointer_cast<PositionManager>(mapComponentManagers["PositionManager"]));
        std::shared_ptr<Position> PositionComponent = std::dynamic_pointer_cast<Position>(PositionManager->getComponent(entity));
        if (PositionComponent == nullptr)
            return;
        float x = va_arg(ptr, float);
        float y = va_arg(ptr, float);
        float z = va_arg(ptr, float);
        
        PositionComponent->setPosition(x ,y, z);
    }

    void SystemSetPosition::update(std::unordered_map<std::string, 
    std::shared_ptr<IComponentManager>> *mapComponentManger, 
    std::vector<std::shared_ptr<Entity>> *entities)
    {
    }

    SystemSetPosition::SystemSetPosition()
    {
    }

    SystemSetPosition::~SystemSetPosition()
    {
    }
}

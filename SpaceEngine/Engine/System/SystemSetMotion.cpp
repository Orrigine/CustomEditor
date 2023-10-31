/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** SystemSetMotion
*/

#include "SystemSetMotion.hpp"

namespace SpaceEngine {
        void SystemSetMotion::init(std::unordered_map<std::string,
    std::shared_ptr<IComponentManager>> mapComponentManagers, 
    std::shared_ptr<Entity> entity, std::string component, va_list ptr)
    {
        if (component !=  "Motion")
            return;
        std::shared_ptr<MotionManager> MotionManager(std::dynamic_pointer_cast<MotionManager>(mapComponentManagers["MotionManager"]));
        std::shared_ptr<Motion> MotionComponent = std::dynamic_pointer_cast<Motion>(MotionManager->getComponent(entity));
        if (MotionComponent == nullptr)
            return;
        float vX = va_arg(ptr, float);
        float vY = va_arg(ptr, float);
        float vZ = va_arg(ptr, float);
        float aX = va_arg(ptr, float);
        float aY = va_arg(ptr, float);
        float aZ = va_arg(ptr, float);
        
        MotionComponent->setMotion(vX, vY, vZ, aX, aY, aZ);
    }

    void SystemSetMotion::update(std::unordered_map<std::string, 
    std::shared_ptr<IComponentManager>> *mapComponentManger, 
    std::vector<std::shared_ptr<Entity>> *entities)
    {
    }

    SystemSetMotion::SystemSetMotion()
    {
    }

    SystemSetMotion::~SystemSetMotion()
    {
    }
}
/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** MotionManager
*/

#include "MotionManager.hpp"

namespace SpaceEngine {
    MotionManager::MotionManager()
    {
        _mapType[CHARACTER] = 1;
        _mapType[BULLET] = 1;
        _nbrEntity = 0;
    }

    MotionManager::~MotionManager()
    {
    }
    
    std::shared_ptr<IComponent> MotionManager::getComponent(std::shared_ptr<Entity> entity)
    {
        if (!_mapComponent[entity])
            return NULL;
        return _mapComponent[entity];
    }

    std::vector<std::shared_ptr<Entity>> MotionManager::getAllEntity(void) const
    {
        return (_entityArray);
    }

    void MotionManager::addEntity(std::shared_ptr<Entity> ptr)
    {
        if (!_mapType[ptr->getType()])
            return;
        _nbrEntity += 1;
        _entityArray.push_back(ptr);
        std::shared_ptr<Motion> component(new Motion());
        _mapComponent[ptr] = component;
    }

    
}
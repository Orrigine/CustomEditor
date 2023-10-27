/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** PositionManager
*/

#include "PositionManager.hpp"

namespace SpaceEngine {
    PositionManager::PositionManager()
    {
        _mapType[CHARACTER] = 1;
        _mapType[BULLET] = 1;
        _nbrEntity = 0;
    }

    PositionManager::~PositionManager()
    {
    }
    
    std::shared_ptr<IComponent> PositionManager::getComponent(std::shared_ptr<Entity> entity)
    {
        if (!_mapComponent[entity])
            return NULL;
        return _mapComponent[entity];
    }

    std::vector<std::shared_ptr<Entity>> PositionManager::getAllEntity(void) const
    {
        return (_entityArray);
    }

    void PositionManager::addEntity(std::shared_ptr<Entity> ptr)
    {
        if (!_mapType[ptr->getType()])
            return;
        _nbrEntity += 1;
        _entityArray.push_back(ptr);
        std::shared_ptr<Position> component(new Position());
        _mapComponent[ptr] = component;
    }

    
}
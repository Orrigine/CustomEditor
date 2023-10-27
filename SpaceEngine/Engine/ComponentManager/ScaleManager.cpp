/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** ScaleManager
*/

#include "ScaleManager.hpp"

namespace SpaceEngine {
    ScaleManager::ScaleManager()
    {
        _mapType[CHARACTER] = 1;
        _mapType[BULLET] = 1;
        _nbrEntity = 0;
    }

    ScaleManager::~ScaleManager()
    {
    }
    
    std::shared_ptr<IComponent> ScaleManager::getComponent(std::shared_ptr<Entity> entity)
    {
        if (!_mapComponent[entity])
            return NULL;
        return _mapComponent[entity];
    }

    std::vector<std::shared_ptr<Entity>> ScaleManager::getAllEntity(void) const
    {
        return (_entityArray);
    }

    void ScaleManager::addEntity(std::shared_ptr<Entity> ptr)
    {
        if (!_mapType[ptr->getType()])
            return;
        _nbrEntity += 1;
        _entityArray.push_back(ptr);
        std::shared_ptr<Scale> component(new Scale());
        _mapComponent[ptr] = component;
    }

    
}
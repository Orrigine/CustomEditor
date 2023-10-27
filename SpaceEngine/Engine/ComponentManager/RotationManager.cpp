/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** RotationManager
*/

#include "RotationManager.hpp"

namespace SpaceEngine {
    RotationManager::RotationManager()
    {
        _mapType[CHARACTER] = 1;
        _mapType[BULLET] = 1;
        _nbrEntity = 0;
    }

    RotationManager::~RotationManager()
    {
    }
    
    std::shared_ptr<IComponent> RotationManager::getComponent(std::shared_ptr<Entity> entity)
    {
        if (!_mapComponent[entity])
            return NULL;
        return _mapComponent[entity];
    }

    std::vector<std::shared_ptr<Entity>> RotationManager::getAllEntity(void) const
    {
        return (_entityArray);
    }

    void RotationManager::addEntity(std::shared_ptr<Entity> ptr)
    {
        if (!_mapType[ptr->getType()])
            return;
        _nbrEntity += 1;
        _entityArray.push_back(ptr);
        std::shared_ptr<Rotation> component(new Rotation());
        _mapComponent[ptr] = component;
    }

    
}
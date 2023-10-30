/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** HealthManager
*/

#include "HealthManager.hpp"

namespace SpaceEngine {
    HealthManager::HealthManager()
    {
        _mapType[CHARACTER] = 1;
        _mapType[BULLET] = 0;
        _nbrEntity = 0;
    }

    HealthManager::~HealthManager()
    {
    }
    
    std::shared_ptr<IComponent> HealthManager::getComponent(std::shared_ptr<Entity> entity)
    {
        if (!_mapComponent[entity])
            return NULL;
        return _mapComponent[entity];
    }

    std::vector<std::shared_ptr<Entity>> HealthManager::getAllEntity(void) const
    {
        return (_entityArray);
    }

    void HealthManager::addEntity(std::shared_ptr<Entity> ptr)
    {
        if (!_mapType[ptr->getType()])
            return;
        _nbrEntity += 1;
        _entityArray.push_back(ptr);
        std::shared_ptr<Health> component(new Health());
        _mapComponent[ptr] = component;
    }

    
}
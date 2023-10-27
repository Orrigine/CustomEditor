/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** ColorManager
*/

#include "ColorManager.hpp"

namespace SpaceEngine {
    ColorManager::ColorManager()
    {
        _mapType[CHARACTER] = 1;
        _mapType[BULLET] = 1;
        _nbrEntity = 0;
    }

    ColorManager::~ColorManager()
    {
    }
    
    std::shared_ptr<IComponent> ColorManager::getComponent(std::shared_ptr<Entity> entity)
    {
        if (!_mapComponent[entity])
            return NULL;
        return _mapComponent[entity];
    }

    std::vector<std::shared_ptr<Entity>> ColorManager::getAllEntity(void) const
    {
        return (_entityArray);
    }

    void ColorManager::addEntity(std::shared_ptr<Entity> ptr)
    {
        if (!_mapType[ptr->getType()])
            return;
        _nbrEntity += 1;
        _entityArray.push_back(ptr);
        std::shared_ptr<Color> component(new Color(0, 0, 0));
        _mapComponent[ptr] = component;
    }

    
}
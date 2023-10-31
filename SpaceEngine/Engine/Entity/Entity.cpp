/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Entity
*/

#include "Entity.hpp"

namespace SpaceEngine {
    Entity::Entity(std::string type, std::string name)
    {
        _id = SpaceEngine::id + 1;
        _name = name;
        _type = type;
        SpaceEngine::id += 1;
    }

    Entity::~Entity()
    {
    }

    unsigned int Entity::getId() const
    {
        return (_id);
    }

    std::string Entity::getType() const
    {
        return (_type);
    }

    std::string Entity::getName() const
    {
        return _name;
    }
}
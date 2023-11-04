/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** Entity
*/

#include "Entity.hpp"

namespace SpaceEngine {
    std::unordered_map<std::string, std::vector<Entity *>> Entity::_entitiesMapType;
    std::unordered_map <std::string, Entity *> Entity::_entitiesMapName;
    std::unordered_map <unsigned int, Entity *> Entity::_entitiesMapId;

    void print(std::string mess)
    {
        std::wstring res(mess.begin(), mess.end());
        OutputDebugStringW(res.c_str());
    }
}
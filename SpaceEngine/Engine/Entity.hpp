/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <Windows.h>

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Component/IComponent.hpp"
#include "Graphics/Ligths/GlobalLigths.h"
#include "Graphics/Ligths/Directional/DirectionalLigths.h"
#include "Component/Transform.cpp"


namespace SpaceEngine {
    static unsigned int id = 0;

    class Entity {
        public:
        Entity(std::string name, std::string type = "Default") 
        {
            _id = SpaceEngine::id + 1;
            _name = name;
            _type = type;
            _isActive = true;
            SpaceEngine::id += 1;

            _entitiesMapId[_id] = this;
            _entitiesMapName[_name] = this;
            _entitiesMapType[_type].push_back(this);
        }
        
        ~Entity()
        {
        }
        
        unsigned int getId() const
        {
            return _id;
        }

        std::string getType() const
        {
            return _type;
        }

        std::string getName() const
        {
            return _name;
        }

        bool getStatus() const
        {
            return _isActive;
        }

        // Adds a component class of type componentType to the GameObject.
        template<class T>
        std::shared_ptr<T> addComponent() {
            std::shared_ptr<T> component(new T());
            component->addEntity(this->_id, component);
            _componentsList.push_back(component);
            return component;
        }

        // Gets a reference to a component of type T on the specified GameObject.
        template<class U>
        std::shared_ptr<U> getComponent() {
            for (int i = 0; i < _componentsList.size(); i++) {
                if (std::dynamic_pointer_cast<U>(_componentsList[i]))
                    return std::dynamic_pointer_cast<U>(_componentsList[i]);
            }
            return nullptr;
        }

        // Gets T[] a vector containing all matching components of type T
        template<class V>
        std::vector<std::shared_ptr<V>> getComponents() {
            std::vector<std::shared_ptr<V>> components;
            for (int i = 0; i < _componentsList.size(); i++) {
                if (std::dynamic_pointer_cast<V>(_componentsList[i]))
                    components.push_back(std::dynamic_pointer_cast<V>(_componentsList[i]));
            }
            return components;
        }

        // Is this entity of Type type ?
        bool compareType(std::string type) {
            return type.compare(_type);
        }

        // Activates/Deactivates the entity, depending on 
        // the given true or false value.
        void setActive(bool isActive) {
            _isActive = isActive;
        }

        /* STATIC METHOD  */
        // Finds a GameObject by name and returns it.
        static Entity *find(std::string name)
        {
            return _entitiesMapName[name];
        }

        static Entity *findEntityWithType(std::string type)
        {
            if (_entitiesMapType[type].size())
                return _entitiesMapType[type][0];
            return nullptr;
        }
        
        static std::vector<Entity *> findEntitiesWithType(std::string type)
        {
            return _entitiesMapType[type];
        }

        void putGlobalLight(GlobalLigths* newGlobalLigths) {
            _globalLigths = newGlobalLigths;
        }
        void putDirectionLight(std::list<DirectionalLigths*> newDirectionLigths) {
            _directionalLigths = newDirectionLigths;
        }

        float calculIntensityLight(DirectionalLigths* dir) {
             Vector3f  a =SpaceEngine::Transform::getComponents()[this->_id].get()->getPosition();
             DirectX::XMFLOAT3 b = dir->getPosition();
             return (std::sqrt((float)std::pow(a.x + b.x, 2) + (float)std::pow(a.y + b.y, 2) + (float)std::pow(a.z + b.z, 2)) > dir->getIntensity()) ? 0 : std::sqrt(std::pow(a.x + b.x, 2) + std::pow(a.y + b.y, 2) + std::pow(a.z + b.z, 2)) / dir->getIntensity();

        };
        
        // Get Scene Returns the Scene of a GameObject given by instance ID.

        private:
            // transform
            //scene
            unsigned int _id;
            std::string _name;
            std::string _type;
            bool _isActive;
            GlobalLigths* _globalLigths;
            std::list<DirectionalLigths*> _directionalLigths;

            std::vector<std::shared_ptr<IComponent>> _componentsList;
            // It bind a type with all entities of this type
            // When creating a new entity we add it here with his tag
            // When changing his type we remove the entity from its previous 
            // field and add it to his new one
            static std::unordered_map<std::string, std::vector<Entity *>> _entitiesMapType;
            // Map an entity with its name
            static std::unordered_map <std::string, Entity *> _entitiesMapName;
            static std::unordered_map <unsigned int, Entity *> _entitiesMapId;
    };

    void print(std::string mess);
}
#endif /* !ENTITY_HPP_ */

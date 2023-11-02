/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** IComponentManager
*/

#ifndef ICOMPONENTMANAGER_HPP_
#define ICOMPONENTMANAGER_HPP_

#include "../Entities.hpp"
#include "../Components.hpp"

#include <vector>
#include <unordered_map>
#include <memory>

namespace SpaceEngine {
    class IComponentManager {
        public:
            /**
             * @brief Destroy the IComponentManager object
             * 
             */
            virtual ~IComponentManager() = default;
            /**
             * @brief Maps an empty component to an Entity
             * 
             * @param ptr 
             */
            virtual void addEntity(std::shared_ptr<Entity> ptr) = 0;
            /**
             * @brief Get the Component of an entity
             * 
             * @param entity 
             * @return std::shared_ptr<IComponent> 
             */
            virtual std::shared_ptr<IComponent> getComponent(std::shared_ptr<Entity> entity) = 0;
        protected:
        private:
    };
}

#endif /* !ICOMPONENTMANAGER_HPP_ */

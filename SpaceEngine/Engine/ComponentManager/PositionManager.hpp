/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** PositionManager
*/

#ifndef POSITIONMANAGER_HPP_
#define POSITIONMANAGER_HPP_

#include "IComponentManager.hpp"

namespace SpaceEngine {
    class PositionManager : public IComponentManager {
        public:
            /**
             * @brief Construct a new Position Manager object
             * 
             */
            PositionManager();
            /**
             * @brief Destroy the Position Manager object
             * 
             */
            ~PositionManager();
            /**
             * Add a new entity to the PositionManager
             * @param ptr This is the new entity to add to the Manager
             */
            void addEntity(std::shared_ptr<Entity> ptr);
            
            /**
             * Get all the entity that the PositionManager contains
             * @return std::vector<std::shared_ptr<Entity>> A vector which contains the Id
             * of all the entities that the manger contains
             */
            std::vector<std::shared_ptr<Entity>> getAllEntity() const;

            /**
             * @brief Get the Component object
             * 
             * @param entity 
             * @return std::shared_ptr<IComponent> 
             */
            std::shared_ptr<IComponent> getComponent(std::shared_ptr<Entity> entity);
        
        private:
            std::unordered_map<entityType, bool> _mapType; /*< A map that define if the manager hold a type of Entity*/
            std::vector<std::shared_ptr<Entity>> _entityArray; /*< The id of all entities that the manger contains */
            std::unordered_map<std::shared_ptr<Entity>, std::shared_ptr<Position>> _mapComponent; /*< The component associated to each entity*/
            int _nbrEntity; /*< The number of entities */
        protected:
        private:
    };
}

#endif /* !POSITIONMANAGER_HPP_ */

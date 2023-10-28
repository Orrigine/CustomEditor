/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** ScaleManager
*/

#ifndef SCALEMANAGER_HPP_
#define SCALEMANAGER_HPP_

#include "IComponentManager.hpp"

namespace SpaceEngine {
    class ScaleManager : public IComponentManager {
        public:
            /**
             * @brief Construct a new Scale Manager object
             * 
             */
            ScaleManager();
            /**
             * @brief Destroy the Scale Manager object
             * 
             */
            ~ScaleManager();
            /**
             * Add a new entity to the ScaleManager
             * @param ptr This is the new entity to add to the Manager
             */
            void addEntity(std::shared_ptr<Entity> ptr);
            
            /**
             * Get all the entity that the ScaleManager contains
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
            std::unordered_map<std::shared_ptr<Entity>, std::shared_ptr<Scale>> _mapComponent; /*< The component associated to each entity*/
            int _nbrEntity; /*< The number of entities */
        protected:
        private:
    };
}

#endif /* !SCALEMANAGER_HPP_ */

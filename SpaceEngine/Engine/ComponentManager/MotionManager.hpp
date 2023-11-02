/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** MotionManager
*/

#ifndef MOTIONMANAGER_HPP_
#define MOTIONMANAGER_HPP_

#include "IComponentManager.hpp"

namespace SpaceEngine {
    class MotionManager : public IComponentManager {
        public:
            /**
             * @brief Construct a new Motion Manager object
             * 
             */
            MotionManager();
            /**
             * @brief Destroy the Motion Manager object
             * 
             */
            ~MotionManager();
            /**
             * Add a new entity to the MotionManager
             * @param ptr This is the new entity to add to the Manager
             */
            void addEntity(std::shared_ptr<Entity> ptr);
            
            /**
             * Get all the entity that the MotionManager contains
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
            std::unordered_map<std::shared_ptr<Entity>, std::shared_ptr<Motion>> _mapComponent; /*< The component associated to each entity*/
            int _nbrEntity; /*< The number of entities */
        protected:
        private:
    };
}

#endif /* !MOTIONMANAGER_HPP_ */

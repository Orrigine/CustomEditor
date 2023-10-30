/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** SystemSetMotion
*/

#ifndef SYSTEMSETMOTION_HPP_
#define SYSTEMSETMOTION_HPP_

#include "ISystem.hpp"

namespace SpaceEngine {
    class SystemSetMotion : ISystem
    {
        public:
            /**
             * @brief Construct a new System Set Motion object
             * 
             */
            SystemSetMotion();
            /**
             * @brief Destroy the System Set Motion object
             * 
             */
            ~SystemSetMotion();
            /**
             * @brief update the system attribute each frame
             * 
             * @param mapComponentManger 
             * @param entities 
             */
            void update(std::unordered_map<std::string, 
            std::shared_ptr<IComponentManager>> *mapComponentManger, 
            std::vector<std::shared_ptr<Entity>> *entities);
            /**
             * @brief set the motion of an entity
             * 
             * @param mapComponentManagers 
             * @param entity 
             * @param component 
             * @param ptr 
             */
            void init(std::unordered_map<std::string, 
            std::shared_ptr<IComponentManager>> 
            mapComponentManagers, std::shared_ptr<Entity> entity, 
            std::string component, va_list ptr);
    };
}

#endif /* !SYSTEMSETMOTION_HPP_ */

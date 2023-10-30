/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** SystemSetPosition
*/

#ifndef SYSTEMSETPOSITION_HPP_
#define SYSTEMSETPOSITION_HPP_

#include "ISystem.hpp"

namespace SpaceEngine {
    class SystemSetPosition : public ISystem
    {
        public:
            /**
             * @brief Construct a new System Set Position object
             * 
             */
            SystemSetPosition();
            /**
             * @brief Destroy the System Set Position object
             * 
             */
            ~SystemSetPosition();
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
             * @brief set the position of an entity
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

#endif /* !SYSTEMSETPOSITION_HPP_ */

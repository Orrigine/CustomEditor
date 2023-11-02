/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** SystemSetColor
*/

#ifndef SYSTEMSETCOLOR_HPP_
#define SYSTEMSETCOLOR_HPP_

#include "ISystem.hpp"

namespace SpaceEngine {
    class SystemSetColor : public ISystem
    {
        public:
            /**
             * @brief Construct a new System Set Color object
             * 
             */
            SystemSetColor();
            /**
             * @brief Destroy the System Set Color object
             * 
             */
            ~SystemSetColor();
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
             * @brief set the color of an entity
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

#endif /* !SYSTEMSETCOLOR_HPP_ */

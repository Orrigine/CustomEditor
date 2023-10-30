/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** SystemSetScale
*/

#ifndef SYSTEMSETSCALE_HPP_
#define SYSTEMSETSCALE_HPP_

#include "ISystem.hpp"

namespace SpaceEngine {
    class SystemSetScale : public ISystem
    {
        public:
            /**
             * @brief Construct a new System Set Scale object
             * 
             */
            SystemSetScale();
            /**
             * @brief Destroy the System Set Scale object
             * 
             */
            ~SystemSetScale();
            /**
             * @brief update the system attribute each frame
             * 
             */
            void update(std::unordered_map<std::string, 
            std::shared_ptr<IComponentManager>> *mapComponentManger, 
            std::vector<std::shared_ptr<Entity>> *entities);
            /**
             * @brief set the scale of an entity
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

#endif /* !SYSTEMSETSCALE_HPP_ */

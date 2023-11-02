/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** SystemSetRotation
*/

#ifndef SYSTEMSETROTATION_HPP_
#define SYSTEMSETROTATION_HPP_

#include "ISystem.hpp"

namespace SpaceEngine {
    class SystemSetRotation : public ISystem 
    {
        public:
            /**
             * @brief Construct a new System Set Rotation object
             * 
             */
            SystemSetRotation();
            /**
             * @brief Destroy the System Set Rotation object
             * 
             */
            ~SystemSetRotation();
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
             * @brief set the rotation of an entity
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

#endif /* !SYSTEMSETROTATION_HPP_ */

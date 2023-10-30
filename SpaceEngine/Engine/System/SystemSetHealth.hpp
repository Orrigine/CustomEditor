/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** SystemSetHealth
*/

#ifndef SYSTEMSETHEALTH_HPP_
#define SYSTEMSETHEALTH_HPP_

#include "ISystem.hpp"

namespace SpaceEngine {
    class SystemSetHealth : public ISystem
    {
        public:
            /**
             * @brief Construct a new System Set Health object
             * 
             */
            SystemSetHealth();
            /**
             * @brief Destroy the System Set Health object
             * 
             */
            ~SystemSetHealth();
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
             * @brief set the health of an entity
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
#endif /* !SYSTEMSETHEALTH_HPP_ */

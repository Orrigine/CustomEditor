/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** ISystem
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

#include "../Entities.hpp"
#include "../Components.hpp"
#include "../ComponentManagers.hpp"
#include <memory>
#include <cstdarg>
#include <unordered_map>

namespace SpaceEngine {
    class ISystem {
        public:
            virtual void update(std::unordered_map<std::string, 
            std::shared_ptr<IComponentManager>> *mapComponentManger,
            std::vector<std::shared_ptr<Entity>> *entities) = 0;
            virtual void init(std::unordered_map<std::string,
            std::shared_ptr<IComponentManager>> mapComponentManagers,
            std::shared_ptr<Entity> entity, std::string component,
            va_list ptr) = 0;
        protected:
        private:
    };
}
#endif /* !ISYSTEM_HPP_ */

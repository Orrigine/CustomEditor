/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_
#include "../Entity.hpp"
#include <memory>

namespace SpaceEngine {
    struct Vector3f {
        float x;
        float y;
        float z;
    };

    class IComponent {
        public:
            /**
             * @brief Destroy the IComponent object
             * 
             */
            virtual ~IComponent() = default;
        protected:
        private:
            // The entity this component is attached to
            std::shared_ptr<Entity> _entity;
    };
}

#endif /* !ICOMPONENT_HPP_ */

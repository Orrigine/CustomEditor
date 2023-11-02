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
    //        static virtual void addEntity(unsigned int entityId, std::shared_ptr<IComponent> component) = 0;
        protected:
        private:
            // The entity this component is attached to
    };
}

#endif /* !ICOMPONENT_HPP_ */

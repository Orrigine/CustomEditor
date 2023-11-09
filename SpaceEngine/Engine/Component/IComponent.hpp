/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_
#include <memory>
#include <string>
#include <unordered_map>

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
            virtual void init(void* engine, void* renderApp) = 0;
            virtual void update(void* engine, void* renderApp) = 0;
    //        static virtual void addEntity(unsigned int entityId, std::shared_ptr<IComponent> component) = 0;
        protected:
        private:
            // The entity this component is attached to
    };
}

#endif /* !ICOMPONENT_HPP_ */

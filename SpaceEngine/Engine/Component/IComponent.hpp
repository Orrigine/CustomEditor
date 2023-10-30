/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

namespace SpaceEngine {
    class IComponent {
        public:
            /**
             * @brief Destroy the IComponent object
             * 
             */
            virtual ~IComponent() = default;
        protected:
        private:
    };
}

#endif /* !ICOMPONENT_HPP_ */

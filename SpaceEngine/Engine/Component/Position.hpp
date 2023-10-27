/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include "IComponent.hpp"

namespace SpaceEngine {
    class Position : public IComponent
    {
        public:
            /**
             * @brief Construct a new Position Component
             * 
             * @param x 
             * @param y 
             * @param z 
             */
            Position(float x = 0, float y = 0, float z = 0);
            /**
             * @brief Destroy the Position component
             * 
             */
            ~Position();
            /**
             * @brief Set the Position values
             * 
             * @param x 
             * @param y 
             * @param z 
             */
            void setPosition(float x, float y, float z);
            /**
             * @brief get the X postion
             * 
             * @return float 
             */
            float getX() const;
            /**
             * @brief Get the Y position
             * 
             * @return float 
             */
            float getY() const;
            /**
             * @brief get the Z position
             * 
             * @return float 
             */
            float getZ() const;

        protected:
        private:
            float _x;
            float _y;
            float _z;
    };
}

#endif /* !POSITION_HPP_ */

/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Rotation
*/

#ifndef ROTATION_HPP_
#define ROTATION_HPP_

#include "IComponent.hpp"

namespace SpaceEngine {
    class Rotation : public IComponent
    {
        public:
            /**
             * @brief Construct a new Rotation Component
             * 
             * @param angleX 
             * @param angleY 
             * @param angleZ 
             */
            Rotation(float angleX = 1, float angleY = 1, float angleZ = 1);
            /**
             * @brief Destroy the Rotation component
             * 
             */
            ~Rotation();
            /**
             * @brief Set the Rotation values
             * 
             * @param angleX 
             * @param angleY 
             * @param angleZ 
             */
            void setRotation(float angleX, float angleY, float angleZ);
            /**
             * @brief Get the Angle X value
             * 
             * @return float 
             */
            float getAngleX() const;
            /**
             * @brief Get the Angle Y value
             * 
             * @return float 
             */
            float getAngleY() const;
            /**
             * @brief Get the Angle Z value
             * 
             * @return float 
             */
            float getAngleZ() const;

        protected:
        private:
            float _angleX;
            float _angleY;
            float _angleZ;
    };
}

#endif /* !ROTATION_HPP_ */

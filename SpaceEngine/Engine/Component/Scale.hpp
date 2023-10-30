/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Scale
*/

#ifndef SCALE_HPP_
#define SCALE_HPP_

#include "IComponent.hpp"

namespace SpaceEngine {
    class Scale : public IComponent
    {
        public:
            /**
             * @brief Construct a new Scale Component
             * 
             * @param scaleX 
             * @param scaleY 
             * @param scaleZ 
             */
            Scale(float scaleX = 1, float scaleY = 1, float scaleZ = 1);
            /**
             * @brief Destroy the Scale Component
             * 
             */
            ~Scale();
            /**
             * @brief Set the Scale values
             * 
             * @param scaleX 
             * @param scaleY 
             * @param scaleZ 
             */
            void setScale(float scaleX, float scaleY, float scaleZ);
            /**
             * @brief Get the Scale X value
             * 
             * @return float 
             */
            float getScaleX() const;
            /**
             * @brief Get the Scale Y value
             * 
             * @return float 
             */
            float getScaleY() const;
            /**
             * @brief Get the Scale Z value
             * 
             * @return float 
             */
            float getScaleZ() const;

        protected:
        private:
            float _scaleX;
            float _scaleY;
            float _scaleZ;
    };
}

#endif /* !SCALE_HPP_ */

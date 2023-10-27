/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Motion
*/

#ifndef MOTION_HPP_
#define MOTION_HPP_

#include "IComponent.hpp"

namespace SpaceEngine {
    class Motion : public IComponent
    {
        public:
            /**
             * @brief Construct a new Motion Component
             * 
             * @param vX 
             * @param vY
             * @param vZ 
             * @param aX 
             * @param aY 
             * @param aZ 
             */
            Motion(float vX = 1, float vY = 1, float vZ = 1,
                float aX = 1, float aY = 1, float aZ = 1);
            /**
             * @brief Destroy the Motion component
             * 
             */
            ~Motion();
            /**
             * @brief Set the Motion component values
             * 
             * @param vX 
             * @param vY 
             * @param vZ 
             * @param aX 
             * @param aY 
             * @param aZ 
             */
            void setMotion(float vX, float vY, float vZ, float aX,
            float aY, float aZ);
            /**
             * @brief Get the Vx value
             * 
             * @return float 
             */
            float getVx() const;
            /**
             * @brief Get the Vy value
             * 
             * @return float 
             */
            float getVy() const;
            /**
             * @brief Get the Vz value
             * 
             * @return float 
             */
            float getVz() const;
            /**
             * @brief Get the Ax value
             * 
             * @return float 
             */
            float getAx() const;
            /**
             * @brief Get the Ay value
             * 
             * @return float 
             */
            float getAy() const;
            /**
             * @brief Get the Az value
             * 
             * @return float 
             */
            float getAz() const;
        protected:
        private:
            float _vX;
            float _vY;
            float _vZ;
            float _aX;
            float _aY;
            float _aZ;
    };
}

#endif /* !MOTION_HPP_ */

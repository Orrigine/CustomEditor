/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Health
*/

#ifndef HEALTH_HPP_
#define HEALTH_HPP_

#include "IComponent.hpp"

namespace SpaceEngine {
    class Health : public IComponent
    {
        public:
            /**
             * @brief Construct a new Health Component
             * 
             * @param currentHealth 
             * @param maxHealth 
             */
            Health(int currentHealth = 3, int maxHealth = 3);
            /**
             * @brief Destroy the Health object
             * 
             */
            ~Health();
            /**
             * @brief Set the Current Health value
             * 
             * @param currentHealth 
             */
            void setCurrentHealth(int currentHealth);
            /**
             * @brief Set the Max Health value
             * 
             * @param currentHealth 
             */
            void setMaxHealth(int maxHealth);
            /**
             * @brief Get the Current Health value
             * 
             * @return int 
             */
            int getCurrentHealth() const;
            /**
             * @brief Get the Max Health value
             * 
             * @return int 
             */
            int getMaxHealth() const;
        protected:
        private:
            int _currentHealth;
            int _maxHealth;
    };
}
#endif /* !HEALTH_HPP_ */

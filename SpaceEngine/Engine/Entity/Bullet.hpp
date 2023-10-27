/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Bullet
*/

#ifndef BULLET_HPP_
#define BULLET_HPP_

#include "Entity.hpp"

namespace SpaceEngine {
    class Bullet : public Entity {
        public:
            /**
             * @brief Construct a new Bullet Entity
             * 
             * @param name 
             */
            Bullet(std::string name = "Bullet");
            /**
             * @brief Destroy the Bullet
             * 
             */
            ~Bullet();

        protected:
        private:
    };
}

#endif /* !BULLET_HPP_ */

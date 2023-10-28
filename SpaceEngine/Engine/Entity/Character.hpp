/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Character
*/

#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include "Entity.hpp"

namespace SpaceEngine {
    class Character : public Entity
    {
        public:
            /**
             * @brief Construct a new Character Entity
             * 
             * @param name Entity Name
             */
            Character(std::string name = "Character");

            /**
             * @brief Destroy the Character Entity
             * 
             */
            ~Character();
        protected:
        private:
    };
}
#endif /* !CHARACTER_HPP_ */

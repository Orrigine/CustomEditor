/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_
#include <string>

namespace SpaceEngine{
    static unsigned int id = 0;

    class Entity {
        public:
        /**
         * @brief Construct a new Entity object
         * 
         * @param type 
         * @param name 
         */
        Entity(std::string type, std::string name = "");
        /**
         * @brief Destroy the Entity object
         * 
         */
        ~Entity();
        /**
         * @brief Return the entity Id
         * 
         * @return unsigned int 
         */
        unsigned int getId() const;
        /**
         * @brief Return the entity type
         * 
         * @return entityType 
         */
        std::string getType() const;
        /**
         * @brief Return the entity's name
         * 
         * @return std::string 
         */
        std::string getName() const;

        protected:
            unsigned int _id;
            std::string _name;
            std::string _type;
    };
}
#endif /* !ENTITY_HPP_ */

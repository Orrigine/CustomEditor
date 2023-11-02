/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Color
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include "IComponent.hpp"

namespace SpaceEngine {
    class Color : public IComponent
    {
        public:
            /**
             * @brief Construct a new Color Component
             * 
             * @param red 
             * @param green 
             * @param blue 
             * @param alpha 
             */
            Color(unsigned int red = 0, unsigned int green = 0, 
            unsigned int blue = 0, unsigned int alpha = 1);
            /**
             * @brief Destroy the Color Component
             * 
             */
            ~Color();
            /**
             * @brief Set the Color component values
             * 
             * @param red 
             * @param green 
             * @param blue 
             * @param alpha 
             */
            void setColor(unsigned int red, unsigned int green, unsigned int blue,
            unsigned int alpha);
            /**
             * @brief Get the Color Red chanel
             * 
             * @return unsigned int 
             */
            unsigned int getColorRed() const;
            /**
             * @brief Get the Color Green chanel
             * 
             * @return unsigned int 
             */
            unsigned int getColorGreen() const;
            /**
             * @brief Get the Color Blue chanel
             * 
             * @return unsigned int 
             */
            unsigned int getColorBlue() const;
            /**
             * @brief Get the Color Alpha chanel
             * 
             * @return unsigned int 
             */
            unsigned int getColorAlpha() const;

        protected:
        private:
            unsigned int _red;
            unsigned int _green;
            unsigned int _blue;
            unsigned int _alpha;
    };
}

#endif /* !COLOR_HPP_ */

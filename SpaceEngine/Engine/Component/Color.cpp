/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Color
*/

#include "Color.hpp"

namespace SpaceEngine {
    Color::Color(unsigned int red, unsigned int green, unsigned int blue,
            unsigned int alpha) : _red(red), _green(green), _blue(blue),
            _alpha(alpha)
    {
    }

    Color::~Color()
    {
    }

    void Color::setColor(unsigned int red, unsigned int green, unsigned int blue,
            unsigned int alpha)
    {
        _red = red;
        _green = green;
        _blue = blue;
        _alpha = alpha;
    }

    unsigned int Color::getColorRed() const
    {
        return _red;
    }

    unsigned int Color::getColorGreen() const
    {
        return _green;
    }

    unsigned int Color::getColorBlue() const
    {
        return _blue;
    }

    unsigned int Color::getColorAlpha() const
    {
        return _alpha;
    }
}
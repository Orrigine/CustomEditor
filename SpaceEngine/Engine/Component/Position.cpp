/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Position
*/

#include "Position.hpp"

namespace SpaceEngine {
    Position::Position(float x, float y, float z) :
    _x(x), _y(y), _z(z)
    {
    }

    Position::~Position()
    {
    }

    void Position::setPosition(float x, float y, float z)
    {
        _x = x;
        _y = y;
        _z = z;
    }

    float Position::getX() const
    {
        return _x;
    }

    float Position::getY() const
    {
        return _y;
    }

    float Position::getZ() const
    {
        return _z;
    }
}

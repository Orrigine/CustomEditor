/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Scale
*/

#include "Scale.hpp"

namespace SpaceEngine {
    Scale::Scale(float scaleX, float scaleY, float scaleZ) :
    _scaleX(scaleX), _scaleY(scaleY), _scaleZ(scaleZ)
    {
    }

    Scale::~Scale()
    {
    }

    void Scale::setScale(float scaleX, float scaleY, float scaleZ)
    {
        _scaleX = scaleX;
        _scaleY = scaleY;
        _scaleZ = scaleZ;
    }

    float Scale::getScaleX() const
    {
        return _scaleX;
    }

    float Scale::getScaleY() const
    {
        return _scaleY;
    }

    float Scale::getScaleZ() const
    {
        return _scaleZ;
    }
}
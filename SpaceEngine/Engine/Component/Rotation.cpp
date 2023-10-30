/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Rotation
*/

#include "Rotation.hpp"

namespace SpaceEngine {
    Rotation::Rotation(float angleX, float angleY, float angleZ) :
    _angleX(angleX), _angleY(angleY), _angleZ(angleZ)
    {
    }

    Rotation::~Rotation()
    {
    }

    void Rotation::setRotation(float angleX, float angleY, float angleZ)
    {
        _angleX = angleX;
        _angleY = angleY;
        _angleZ = angleZ;
    }

    float Rotation::getAngleX() const
    {
        return _angleX;
    }

    float Rotation::getAngleY() const
    {
        return _angleY;
    }

    float Rotation::getAngleZ() const
    {
        return _angleZ;
    }
}
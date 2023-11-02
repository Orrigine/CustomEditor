/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Motion
*/

#include "Motion.hpp"

namespace SpaceEngine {
    Motion::Motion(float vX, float vY, float vZ, float aX,
            float aY, float aZ) : _vX(vX), _vY(vY), _vZ(vZ),
            _aX(aX), _aY(aY), _aZ(aZ)
    {
    }

    Motion::~Motion()
    {
    }

    void Motion::setMotion(float vX, float vY, float vZ, float aX,
            float aY, float aZ)
    {
        _vX = vX;
        _vY = vY;
        _vZ = vZ;
        _aX = aX;
        _aY = aY;
        _aZ = aZ;
    }

    float Motion::getVx() const
    {
        return _vX;
    }

    float Motion::getVy() const
    {
        return _vY;
    }

    float Motion::getVz() const
    {
        return _vZ;
    }

    float Motion::getAx() const
    {
        return _aX;
    }

    float Motion::getAy() const
    {
        return _aY;
    }

    float Motion::getAz() const
    {
        return _aZ;
    }
}
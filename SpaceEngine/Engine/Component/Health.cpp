/*
** G-TECH PROJECT, 2023
** SpaceEngine
** File description:
** Health
*/

#include "Health.hpp"

namespace SpaceEngine {
    Health::Health(int currentHealth, int maxHealth) :
    _currentHealth(currentHealth), _maxHealth(maxHealth)
    {
    }

    Health::~Health()
    {
    }

    void Health::setCurrentHealth(int currentHealth)
    {
        _currentHealth = currentHealth;
    }

    void Health::setMaxHealth(int maxHealth)
    {
        _maxHealth = maxHealth;
    }

    int Health::getCurrentHealth() const
    {
        return _currentHealth;
    }

    int Health::getMaxHealth() const
    {
        return _maxHealth;
    }
}
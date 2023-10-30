/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** SystemSetHealth
*/

#include "SystemSetHealth.hpp"

namespace SpaceEngine {
    void SystemSetHealth::init(std::unordered_map<std::string,
    std::shared_ptr<IComponentManager>> mapComponentManagers, 
    std::shared_ptr<Entity> entity, std::string component, va_list ptr)
    {
        if (component !=  "Health")
            return;
        std::shared_ptr<HealthManager> HealthManager(std::dynamic_pointer_cast<HealthManager>(mapComponentManagers["HealthManager"]));
        std::shared_ptr<Health> HealthComponent = std::dynamic_pointer_cast<Health>(HealthManager->getComponent(entity));
        if (HealthComponent == nullptr)
            return;
        int currentHealth = va_arg(ptr, int);
        int maxHealth = va_arg(ptr, int);
        
        HealthComponent->setCurrentHealth(currentHealth);
        HealthComponent->setMaxHealth(maxHealth);

    }

    void SystemSetHealth::update(std::unordered_map<std::string, 
    std::shared_ptr<IComponentManager>> *mapComponentManger, 
    std::vector<std::shared_ptr<Entity>> *entities)
    {
    }

    SystemSetHealth::SystemSetHealth()
    {
    }

    SystemSetHealth::~SystemSetHealth()
    {
    }
}
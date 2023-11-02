/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** SystemSetColor
*/

#include "SystemSetColor.hpp"

namespace SpaceEngine {
    void SystemSetColor::init(std::unordered_map<std::string,
    std::shared_ptr<IComponentManager>> mapComponentManagers, 
    std::shared_ptr<Entity> entity, std::string component, va_list ptr)
    {
        if (component !=  "Color")
            return;
        std::shared_ptr<ColorManager> ColorManager(std::dynamic_pointer_cast<ColorManager>(mapComponentManagers["ColorManager"]));
        std::shared_ptr<Color> ColorComponent = std::dynamic_pointer_cast<Color>(ColorManager->getComponent(entity));
        if (ColorComponent == nullptr)
            return;
        unsigned int red = va_arg(ptr, unsigned int);
        unsigned int green = va_arg(ptr, unsigned int);
        unsigned int blue = va_arg(ptr, unsigned int);
        unsigned int alpha =va_arg(ptr, unsigned int);

        ColorComponent->setColor(red, green, blue, alpha);
    }

    void SystemSetColor::update(std::unordered_map<std::string, 
    std::shared_ptr<IComponentManager>> *mapComponentManger, 
    std::vector<std::shared_ptr<Entity>> *entities)
    {
    }

    SystemSetColor::SystemSetColor()
    {
    }

    SystemSetColor::~SystemSetColor()
    {
    }
}
#pragma once

#include "Engine/Entity.hpp"
#include "Engine/Components.hpp"
#include "Graphics.h"

namespace SpaceEngine {
    class ISystem {
    public:
        /**
         * @brief update the system attribute each frame
         *
         */
        virtual void update(std::unordered_map<unsigned int, std::shared_ptr<Entity>>* sceneEntitiesMap, std::shared_ptr<
            Render::Window> renderApplication) = 0;

        virtual void init(std::unordered_map<unsigned int, std::shared_ptr<Entity>>* sceneEntitiesMap, std::shared_ptr<Render::Window> renderApplication) = 0;
    };
}
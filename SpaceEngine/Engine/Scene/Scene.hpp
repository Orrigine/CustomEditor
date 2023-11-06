/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** Scene
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "Engine/Entity.hpp"
#include "Engine/Components.hpp"

namespace SpaceEngine {
        class Scene {
        public:
            Scene(std::string name);
            ~Scene();
            std::string getName() const;
            std::shared_ptr<Entity> createEntity(std::string name, std::string type = "Default");
            //void lauchScene(std::string sceneName);
            void launchLoop();
            void setLoop(void (*loopPtr)(Scene*));
        private:
            std::string _name;
            std::unordered_map<unsigned int, std::shared_ptr<Entity>> _entitiesMap;
            void (*_loopPtr)(Scene*);
            static std::unordered_map<std::string, Scene*> _sceneMap;
        };
}

#endif /* !SCENE_HPP_ */

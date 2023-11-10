#include "Engine/Components.hpp"
#include "Engine/Entity.hpp"
#include "Engine/System/RenderSystem.h"
#include "Engine/System/ScriptSystem.h"
// #include "Engine/Scene/Scene.hpp"

#include "Graphics.h"

namespace SpaceEngine
{
    class Engine
    {
    public:
        Engine(HINSTANCE hInstance);
        ~Engine();
        // init and create d3dapp
        void init();
        int run();
        void createWindow(int width, int height, std::wstring title);
        std::shared_ptr<Entity> createEntity(std::string name, std::string type = "Default");

        // ---- Getters
        std::unordered_map<unsigned int, std::shared_ptr<Entity>> getEntities();
        std::vector<std::shared_ptr<ISystem>> getSystems();
        std::shared_ptr<Render::Window> getRenderApplication();
        std::shared_ptr<Entity> getEntity(std::string name);

    private:
        HINSTANCE _hInstance;
        int _width;
        int _height;
        std::wstring _title;
        std::shared_ptr<Render::Window> _renderApplication;
        std::vector<std::shared_ptr<ISystem>> _systems;
        std::unordered_map<unsigned int, std::shared_ptr<Entity>> _entitiesMap;
        std::unordered_map<std::string, std::shared_ptr<Entity>> _entityNameMap;
        // std::shared_ptr<RenderSystem> _renderSystem;
    };
}
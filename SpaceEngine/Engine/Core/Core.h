#include "Engine/Components.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Scene/Scene.hpp"

#include "Graphics.h"

namespace SpaceEngine {
    class Core {
    public:
        Core(HINSTANCE hInstance);
        ~Core();
        // init and create d3dapp
        void init();
        int run();
        void createWindow(int width, int height, std::wstring title);
        std::shared_ptr<Scene> createScene(std::string name);
        //void lauchScene(std::string name);
        std::shared_ptr<Scene> getScene(std::string name);
        void setStartScene(std::string name);
        //void setWindow(/*win*/);

    private:
        HINSTANCE _hInstance;
        int _width;
        int _height;
        std::wstring _title;
        std::shared_ptr<Render::Window> _renderApplication;

        std::string _startScene;
        std::unordered_map<std::string, std::shared_ptr<Scene>> _mapScene;
        std::shared_ptr<RenderSystem> _renderSystem;
    };
}
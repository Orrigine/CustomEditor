#include "Core.h"

namespace SpaceEngine {
    
    Core::Core(HINSTANCE hInstance) : _hInstance(hInstance), _startScene(""),
        _renderApplication(new Render::Window(hInstance))
    {
    }

    Core::~Core()
    {
    }

    void Core::createWindow(int width, int height, std::wstring title)
    {
        _width = width;
        _height = height;
        _title = title;
    }

    void Core::init()
    {
        //_renderApplication->Initialize();
    }

    int Core::run()
    {
        try
        {
            if (!_renderApplication->Initialize()) {
                print("############################################################################\n");
                return 84;
            }
            else
                return(_renderApplication->Run());
        }
        catch (DxException& e)
        {
            MessageBox(nullptr, e.ToString().c_str(), L"Engine Failed Init", MB_OK);
            return 84;
        }
        /*std::shared_ptr<Scene> scene = _mapScene[_startScene];
        if (scene)
            scene->launchLoop();*/
        // la scene doit get la render app pour pour voir initialiser la 
        // crea de game object grace aux systemes
        return 0;
    }

    std::shared_ptr<Scene> Core::getScene(std::string name)
    {
        return (_mapScene[name]);
    }
    void Core::setStartScene(std::string name)
    {
        _startScene = name;
    }

    void Core::addScene(std::shared_ptr<Scene> scene)
    {
        _mapScene[scene->getName()] = scene;
    }

};
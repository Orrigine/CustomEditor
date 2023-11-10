#include "Core.h"

namespace SpaceEngine {
    
    Engine::Engine(HINSTANCE hInstance) : _hInstance(hInstance),
        _renderApplication(new Render::Window(hInstance))
    {
        std::shared_ptr<RenderSystem> render(new RenderSystem());
        std::shared_ptr<ScriptSystem> script(new ScriptSystem());
        _systems.push_back(render);
        _systems.push_back(script);

    }

    Engine::~Engine()
    {
    }

    void Engine::createWindow(int width, int height, std::wstring title)
    {
        _width = width;
        _height = height;
        _title = title;
        _renderApplication->setWidth(width);
        _renderApplication->setHeight(height);
        _renderApplication->setWindowName(title);
    }

    void Engine::init()
    {
        _renderApplication->Initialize();
        _renderApplication->setEngine( (void *) this);
    }

    int Engine::run()
    {
        try
        {
            for (int i = 0; i < _systems.size(); i++)
                _systems[i]->init(&_entitiesMap, _renderApplication);
            return(_renderApplication->Run());
        }
        catch (DxException& e)
        {
            MessageBox(nullptr, e.ToString().c_str(), L"Engine Failed Init", MB_OK);
            return 84;
        }
        return 0;
    }

    std::shared_ptr<Entity> Engine::createEntity(std::string name, std::string type)
	{
		std::shared_ptr<Entity> entity(new Entity(name, type));

		entity->addComponent<SpaceEngine::Transform>();
		_entitiesMap[entity->getId()] = entity;
		return entity;
	}

    std::unordered_map<unsigned int, std::shared_ptr<Entity>> Engine::getEntities()
    {
        return _entitiesMap;
    }

    std::vector<std::shared_ptr<ISystem>> Engine::getSystems()
    {
        return _systems;
    }

    std::shared_ptr<Render::Window> Engine::getRenderApplication()
    {
        return _renderApplication;
    }
};
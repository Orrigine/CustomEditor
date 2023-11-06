/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** Scene
*/

#include "Scene.hpp"

namespace SpaceEngine {
	std::unordered_map<std::string, Scene*> _mapScene = {};

	Scene::Scene(std::string name) : _name(name)
	{
		_mapScene[_name] = this;
	}

	Scene::~Scene()
	{
	}

	std::string Scene::getName() const
	{
		return _name;
	}

	std::shared_ptr<Entity> Scene::createEntity(std::string name, std::string type)
	{
		std::shared_ptr<Entity> entity(new Entity(name, type));

		entity->addComponent<SpaceEngine::Transform>();
		_entitiesMap[entity->getId()] = entity;
		return entity;
	}

	void Scene::launchLoop()
	{
		(*_loopPtr)(this);
	}

	void Scene::setLoop(void (*loopPtr)(Scene*))
	{
		_loopPtr = loopPtr;
	}

	void Scene::setRenderApplication(std::shared_ptr<Render::Window> renderApplication)
	{
		_renderApplication = renderApplication;
	}

	std::unordered_map<unsigned int, std::shared_ptr<Entity>> Scene::getAllEntities()
	{
		return _entitiesMap;
	}
}
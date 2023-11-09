#include "ScriptSystem.h"

namespace SpaceEngine {
	ScriptSystem::ScriptSystem()
	{
	}

	ScriptSystem::~ScriptSystem()
	{
	}

	void ScriptSystem::init(
		std::unordered_map<unsigned int, std::shared_ptr<Entity>>*
		sceneEntitiesMap, std::shared_ptr<Render::Window> renderApplication)
	{
	}

	void ScriptSystem::update(std::unordered_map<unsigned int, std::shared_ptr<Entity>>* sceneEntitiesMap, std::shared_ptr<Render::Window> renderApplication)
	{
		std::unordered_map<unsigned int, std::shared_ptr<Script>>
			scriptComponents = Script::getComponents();

		for (auto elm = sceneEntitiesMap->begin(); elm != sceneEntitiesMap->end(); elm++) {
			unsigned int entityId = elm->first;
			if (scriptComponents[entityId]) {
				scriptComponents[entityId]->update(renderApplication->getEngine(), renderApplication.get() );
			}
		}
	}
}
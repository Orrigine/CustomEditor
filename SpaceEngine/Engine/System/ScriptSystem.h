#pragma once

#include "ISystem.h"

namespace SpaceEngine {
	class ScriptSystem : public ISystem
	{
	public:
		ScriptSystem();
		~ScriptSystem();
		void update(std::unordered_map<unsigned int, std::shared_ptr<Entity>>* sceneEntitiesMap, std::shared_ptr<Render::Window> renderApplication);

		void init(std::unordered_map<unsigned int, std::shared_ptr<Entity>>* sceneEntitiesMap, std::shared_ptr<Render::Window> renderApplication);
	};
}
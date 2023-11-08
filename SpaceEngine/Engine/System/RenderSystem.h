#pragma once
#include "ISystem.h"

namespace SpaceEngine {
	class RenderSystem : public ISystem 
	{
	public:
		RenderSystem();
		~RenderSystem();
		void update(std::unordered_map<unsigned int, std::shared_ptr<Entity>>* sceneEntitiesMap, std::shared_ptr<Render::Window> renderApplication);

		void init(std::unordered_map<unsigned int, std::shared_ptr<Entity>>* sceneEntitiesMap, std::shared_ptr<Render::Window> renderApplication);
	};
}

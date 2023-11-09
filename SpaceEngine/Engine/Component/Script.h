/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** Script
*/

#pragma once

#include "IComponent.hpp"

namespace SpaceEngine {
	class Script : public IComponent
	{
	public:
		Script();
		~Script();
		void addEntity(unsigned int entityId, std::shared_ptr<Script> component);
		
		void setScript(void (*ptr) (void*, void*));
		// Get all Script components of the scene
		static std::unordered_map<unsigned int, std::shared_ptr<Script>> getComponents();

		void init(void* engine, void* renderItem);
		void update(void* engine, void* renderItem);

	private:
		int _clock;
		void (*_ptr) (void *, void *);
		unsigned int _entityId;
		static std::unordered_map<unsigned int, std::shared_ptr<Script>> _entitiesScript;
	};
}
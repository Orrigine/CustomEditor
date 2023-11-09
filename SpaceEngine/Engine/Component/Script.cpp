/*
** G - TECH PROJECT, 2023
** SpaceProject
** File description :
** Script
*/

#include "Script.h"

namespace SpaceEngine {
	std::unordered_map<unsigned int, std::shared_ptr<Script>> Script::_entitiesScript = {};

	Script::Script() : _clock(0)
	{
	}

	Script::~Script()
	{
	}

	void Script::addEntity(unsigned int entityId, std::shared_ptr<Script> component)
	{
		_entityId = entityId;
		_entitiesScript[_entityId] = component;
	}

	std::unordered_map<unsigned int, std::shared_ptr<Script>> Script::getComponents()
	{
		return _entitiesScript;
	}

	void Script::setScript(void (*ptr) (void*, void*))
	{
		_ptr = ptr;
	}

	void Script::init(void* engine, void* renderApp)
	{

	}
	void Script::update(void* engine, void* renderApp)
	{
		_ptr(engine, renderApp);
	}
}
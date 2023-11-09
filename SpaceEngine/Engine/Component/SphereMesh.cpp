/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** SphereMesh
*/

#include "SphereMesh.h"

namespace SpaceEngine {
	std::unordered_map<unsigned int, std::shared_ptr<SphereMesh>> SphereMesh::_entitiesSphereMesh = {};

	SphereMesh::SphereMesh() : _isBuild(false), _meshType("sphere")
	{
	}

	SphereMesh::~SphereMesh()
	{
	}

	void SphereMesh::addEntity(unsigned int entityId, std::shared_ptr<SphereMesh> component)
	{
		_entityId = entityId;
		_entitiesSphereMesh[_entityId] = component;
	}

	std::unordered_map<unsigned int, std::shared_ptr<SphereMesh>> SphereMesh::getComponents()
	{
		return _entitiesSphereMesh;
	}

	std::string SphereMesh::getMeshType()
	{
		return _meshType;
	}

	void SphereMesh::init(void* engine, void* renderApp)
	{

	}
	void SphereMesh::update(void* engine, void* renderApp)
	{

	}

	void SphereMesh::setState(bool state) 
	{
		_isBuild = state;
	}
	
	bool SphereMesh::getState() 
	{
		return _isBuild;
	}
}
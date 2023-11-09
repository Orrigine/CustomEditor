/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** SphereMesh
*/
#pragma once

#include "IComponent.hpp"

namespace SpaceEngine {
	class SphereMesh : public IComponent
	{
	public:
		SphereMesh();
		~SphereMesh();
		void addEntity(unsigned int entityId, std::shared_ptr<SphereMesh> component);
		std::string getMeshType();
		void setState(bool state);
		bool getState();

		// Get all SphereMesh components of the scene
		static std::unordered_map<unsigned int, std::shared_ptr<SphereMesh>> getComponents();

		void init(void* engine, void* renderApp);
		void update(void* engine, void* renderApp);

	private:
		bool _isBuild;
		std::string _meshType;
		// std::shared_ptr<Vector3f> Sphere;
		unsigned int _entityId;
		static std::unordered_map<unsigned int, std::shared_ptr<SphereMesh>> _entitiesSphereMesh;
	};
}
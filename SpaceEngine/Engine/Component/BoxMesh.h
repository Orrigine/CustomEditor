/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** BoxMesh
*/

#include "IComponent.hpp"

namespace SpaceEngine {
	class BoxMesh : public IComponent
	{
	public:
		BoxMesh();
		~BoxMesh();
		void addEntity(unsigned int entityId, std::shared_ptr<BoxMesh> component);
		std::string getMeshType();
		void setState(bool state);
		bool getState();

		// Get all BoxMesh components of the scene
		static std::unordered_map<unsigned int, std::shared_ptr<BoxMesh>> getComponents();

		void init(void* engine, void* renderApp);
		void update(void* engine, void* renderApp);

	private:
		bool _isBuild;
		std::string _meshType;
		// std::shared_ptr<Vector3f> box;
		unsigned int _entityId;
		static std::unordered_map<unsigned int, std::shared_ptr<BoxMesh>> _entitiesBoxMesh;
	};
}
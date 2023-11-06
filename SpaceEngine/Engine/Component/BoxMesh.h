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

		// Get all BoxMesh components of the scene
		static std::unordered_map<unsigned int, std::shared_ptr<BoxMesh>> getComponents();

	private:
		// std::shared_ptr<Vector3f> box;
		unsigned int _entityId;

		static std::unordered_map<unsigned int, std::shared_ptr<BoxMesh>> _entitiesBoxMesh;
	};
}
/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** Transform
*/

#include "IComponent.hpp"

namespace SpaceEngine {
	class Transform : public IComponent
	{
	public:
		Transform();
		~Transform();
		void addEntity(unsigned int entityId, std::shared_ptr<Transform> component);
		void setPosition(Vector3f position);
		void setRotation(Vector3f position);
		void setScale(Vector3f position);
		Vector3f getPosition() const;
		Vector3f getRotation() const;
		Vector3f getScale() const;
		// Get all transform components of the scene
		static std::unordered_map<unsigned int, std::shared_ptr<Transform>> getComponents();

	private:
		std::shared_ptr<Vector3f> _position;
		std::shared_ptr<Vector3f> _rotation;
		std::shared_ptr<Vector3f> _scale;
		unsigned int _entityId;

		static std::unordered_map<unsigned int, std::shared_ptr<Transform>> _entitiesTransform;
	};
}
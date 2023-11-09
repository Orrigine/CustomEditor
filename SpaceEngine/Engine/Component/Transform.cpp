/*
** G-TECH PROJECT, 2023
** SpaceProject
** File description:
** Transform
*/

#include "Transform.h"

namespace SpaceEngine {
	std::unordered_map<unsigned int, std::shared_ptr<Transform>> Transform::_entitiesTransform = {};

	Transform::Transform() : _position(new Vector3f), _rotation(new Vector3f),
		_scale(new Vector3f)
	{
		setPosition({ 0.0f, 0.0f, 0.0f });
		setRotation({ 0.0f, 0.0f, 0.0f });
		setScale({ 1.0f, 1.0f, 1.0f });
	}

	Transform::~Transform()
	{
	}

	void Transform::addEntity(unsigned int entityId, std::shared_ptr<Transform> component)
	{
		_entityId = entityId;
		_entitiesTransform[_entityId] = component;
	}

	void Transform::setPosition(Vector3f position)
	{
		_position->x = position.x;
		_position->y = position.y;
		_position->z = position.z;
	}

	void Transform::setRotation(Vector3f rotation)
	{
		_rotation->x = rotation.x;
		_rotation->y = rotation.y;
		_rotation->z = rotation.z;
	}

	void Transform::setScale(Vector3f scale)
	{
		_scale->x = scale.x;
		_scale->y = scale.y;
		_scale->z = scale.z;
	}

	Vector3f Transform::getPosition() const
	{
		Vector3f position = { _position->x, _position->y, _position->z};

		return position;
	}

	Vector3f Transform::getRotation() const
	{
		Vector3f rotation = { _rotation->x, _rotation->y, _rotation->z };

		return rotation;
	}

	Vector3f Transform::getScale() const
	{
		Vector3f scale = { _scale->x, _scale->y, _scale->z };

		return scale;
	}

	std::unordered_map<unsigned int, std::shared_ptr<Transform>> Transform::getComponents()
	{
		return _entitiesTransform;
	}

	void Transform::init(void* engine, void* renderApp)
	{

	}
	void Transform::update(void* engine, void* renderApp)
	{

	}
}
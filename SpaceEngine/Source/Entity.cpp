#include "Headers/Entity.h"

Entity::Entity(TRANSFORM transform, Render::Geometries* Geometries, std::string* filename)
{
	this->m_Transform = transform;
	this->m_Geometries = Geometries;
	this->filename = filename;
}

Entity::~Entity()
{
}

TRANSFORM* Entity::GetTransform()
{
	return &this->m_Transform;
}

void Entity::SetTransform(TRANSFORM newTransform)
{
	this->m_Transform = newTransform;
}

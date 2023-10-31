#pragma once
#include "Tranform/Transform.h"
#include "Geometries.h"
#include <string>
class Entity
{
private:
	TRANSFORM m_Transform;
	Render::Geometries* m_Geometries;
	std::string* filename;

public:
	Entity(TRANSFORM transform , Render::Geometries* Geometries , std::string* filename );
	~Entity();

	TRANSFORM* GetTransform();
	void SetTransform(TRANSFORM newTransform);
	
};


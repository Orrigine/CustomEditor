#pragma once
#include "Tranform/Transform.h"
#include "Geometries.h"
#include <string>
class Entity
{
private:
	//DirectX::XMFLOAT3 posOrigin = { 0,0,0 };
	TRANSFORM m_Transform;
	Render::Geometries* m_Geometries;
	std::string* filename;

public:
	//Creation
	Entity(TRANSFORM transform , Render::Geometries* Geometries , std::string* filename );
	~Entity();

	//Add, Set or Return Transform
	void AddTrasnform(TRANSFORM addTransform);
	void SetTransform(TRANSFORM newTransform);
	TRANSFORM* GetTransform();
	
	//Return Point 
	std::list<Vertex> ReturnPoint();
	//Return the Order of DrawPoint
	std::list<float>ReturnOrderPoint();
	//Return the FileName of Shader
	std::string ReturnShaderFileName();
	//Cacul position of different Point (Use in ReturnPoint())
	DirectX::XMFLOAT3 CalculPosReturn(DirectX::XMFLOAT3 Pos);

};


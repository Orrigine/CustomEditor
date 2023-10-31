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
	#pragma region Creation
		Entity(TRANSFORM transform , Render::Geometries* Geometries , std::string* filename );
		~Entity();
	#pragma endregion
	#pragma region Add, Set or Return Transform
		void addTrasnform(TRANSFORM addTransform);
		void setTransform(TRANSFORM newTransform);
		TRANSFORM* getTransform();

	#pragma endregion
	#pragma region Return Point, Order, ShaderFile
		std::list<Vertex> returnPoint();
		std::list<float>returnOrderPoint();
		std::string returnShaderFileName();
	#pragma endregion
	#pragma region Calcul
		DirectX::XMFLOAT3 calculPosReturn(DirectX::XMFLOAT3 Pos);
	#pragma endregion
};


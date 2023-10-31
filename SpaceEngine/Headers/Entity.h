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
		void AddTrasnform(TRANSFORM addTransform);
		void SetTransform(TRANSFORM newTransform);
		TRANSFORM* GetTransform();

	#pragma endregion
	#pragma region Return Point, Order, ShaderFile
		std::list<Vertex> ReturnPoint();
		std::list<float>ReturnOrderPoint();
		std::string ReturnShaderFileName();
	#pragma endregion
	#pragma region Calcul
		DirectX::XMFLOAT3 CalculPosReturn(DirectX::XMFLOAT3 Pos);
	#pragma endregion
};


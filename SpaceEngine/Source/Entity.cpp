#include "Headers/Entity.h"

#pragma region Creation
	Entity::Entity(TRANSFORM transform, Render::Geometries* Geometries, std::string* filename)
{
	this->m_Transform = transform;
	this->m_Geometries = Geometries;
	this->filename = filename;
}
	Entity::~Entity()
{
}
#pragma endregion
#pragma region Add, Set or Return Transform
	void Entity::addTrasnform(TRANSFORM addTransform)
{
	this->m_Transform.mRot			+= addTransform.mRot;
	this->m_Transform.vScale		= addTransform.vScale;	
	this->m_Transform.vTranslation	= addTransform.vTranslation;
}
	void Entity::setTransform(TRANSFORM newTransform)
{
	this->m_Transform = newTransform;
}
	TRANSFORM* Entity::getTransform()
{
	return &this->m_Transform;
}
#pragma endregion
#pragma region Return Point, Order, ShaderFile
	std::list<Vertex> Entity::returnPoint()
{
	std::list<Vertex> base;
	for (const Vertex& c : this->m_Geometries->ReturnPoints()) {
		base.push_back(
			{
				this->ralculPosReturn(c.position),
				c.color
			}
		);
	}
	

	return base;
}
	std::list<float> Entity::returnOrderPoint()
{
	return this->m_Geometries->returnOrderDraw();
}
	std::string Entity::returnShaderFileName()
{
	return *this->filename;
}
#pragma endregion
#pragma region Calcul
	DirectX::XMFLOAT3 Entity::calculPosReturn(DirectX::XMFLOAT3 Pos)
{
	//Scale
	Pos = {
		Pos.x * this->m_Transform.vScale.x,
		Pos.y * this->m_Transform.vScale.y,
		Pos.z * this->m_Transform.vScale.z
	};
	//Translation
	Pos ={
		Pos.x + this->m_Transform.vTranslation.x,
		Pos.y + this->m_Transform.vTranslation.y,
		Pos.z + this->m_Transform.vTranslation.z
		};
	//Rotation
	Pos = {
		Pos.x * this->m_Transform.mRot.r[0].m128_f32[0] + Pos.x * this->m_Transform.mRot.r[1].m128_f32[0] + Pos.x * this->m_Transform.mRot.r[2].m128_f32[0],
		Pos.y * this->m_Transform.mRot.r[0].m128_f32[1] + Pos.y * this->m_Transform.mRot.r[1].m128_f32[1] + Pos.y * this->m_Transform.mRot.r[2].m128_f32[1],
		Pos.z * this->m_Transform.mRot.r[0].m128_f32[2] + Pos.z * this->m_Transform.mRot.r[1].m128_f32[2] + Pos.z * this->m_Transform.mRot.r[2].m128_f32[2]
	};

	return Pos;
}
#pragma endregion
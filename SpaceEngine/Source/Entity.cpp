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
void Entity::AddTrasnform(TRANSFORM addTransform)
{
	this->m_Transform.mRot			+= addTransform.mRot;
	this->m_Transform.vScale		= addTransform.vScale;	
	this->m_Transform.vTranslation	= addTransform.vTranslation;
}


std::list<Vertex> Entity::ReturnPoint()
{
	std::list<Vertex> base;
	for (const Vertex& c : this->m_Geometries->ReturnPoints()) {
		base.push_back(
			{
				this->CalculPosReturn(c.position),
				c.color
			}
		);
	}
	

	return base;
}
std::list<float> Entity::ReturnOrderPoint()
{
	return this->m_Geometries->ReturnOrderDraw();
}

std::string Entity::ReturnShaderFileName()
{
	return *this->filename;
}

DirectX::XMFLOAT3 Entity::CalculPosReturn(DirectX::XMFLOAT3 Pos)
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

#include "Headers/Geometries.h"


Render::Geometries::Geometries(DirectX::XMFLOAT3 PosOrigin, DirectX::XMMATRIX RotationMatrix)
{
	this->m_PosOrigin = PosOrigin;
	this->m_rotation = RotationMatrix;
}
Render::Geometries::Geometries(DirectX::XMFLOAT3 PosOrigin, DirectX::XMMATRIX RotationMatrix , OrderDraw myOrder[], Vertex myPoint[])
{
	this->m_PosOrigin = PosOrigin;
	this->m_rotation = RotationMatrix;
	for (int i =0 ; i<sizeof(this->m_DrawOrder)/sizeof(OrderDraw);i++)
		this->m_DrawOrder[i] = myOrder[i];
	for (int i = 0; i < sizeof(this->m_PointList) / sizeof(Vertex); i++)
		this->m_PointList[i] = myPoint[i];
}

Render::Geometries::~Geometries()
{

}

void Render::Geometries::AddPoint(Vertex newPoint[])
{
	for(int i =0; i<MAX_POINT ; i++)
		this->m_PointList[i] = newPoint[i];
}

void Render::Geometries::ChangeDrawOrdeer(int Line1, int Line2)
{
	if (0 <= Line1 && Line1 <= MAX_POINT && 0 <= Line2 && Line2 <= MAX_POINT) {
		OrderDraw tpm =this->m_DrawOrder[Line1];
		this->m_DrawOrder[Line1] = this->m_DrawOrder[Line2];
		this->m_DrawOrder[Line2] = tpm;
	}
}

void Render::Geometries::ChangeLineInDraw(OrderDraw newOrder, int Line)
{
	if (0 <= Line && Line <= MAX_POINT) 
		this->m_DrawOrder[Line] = newOrder;
}

void Render::Geometries::TransformGeometries(TRANSFORM Transformation)
{
	if(Transformation.mScale == NULL)
}

#pragma region OtherTransformation

void Render::Geometries::TransformGeometries(DirectX::XMFLOAT3 Scale)
{
	for (int i = 0; i < MAX_POINT; i++) {
		this->m_PointList[i].position.x* Scale.x;
		this->m_PointList[i].position.y* Scale.y;
		this->m_PointList[i].position.z* Scale.z;
	}
}
void Render::Geometries::TransformGeometries(DirectX::XMMATRIX MatrixScale)
{
	DirectX::XMVECTOR a = MatrixScale.r[0];
	DirectX::XMVECTOR b = MatrixScale.r[1];
	DirectX::XMVECTOR c = MatrixScale.r[2];
	
	for (int i = 0; i < MAX_POINT; i++) {
		this->m_PointList[i].position.x = this->m_PointList[i].position.x * a.m128_f32[0] + this->m_PointList[i].position.x * a.m128_f32[1] + this->m_PointList[i].position.x * a.m128_f32[2];
		this->m_PointList[i].position.y = this->m_PointList[i].position.y * b.m128_f32[0] + this->m_PointList[i].position.y * b.m128_f32[1] + this->m_PointList[i].position.y * b.m128_f32[2];
		this->m_PointList[i].position.z = this->m_PointList[i].position.z * c.m128_f32[0] + this->m_PointList[i].position.z * c.m128_f32[1] + this->m_PointList[i].position.z * c.m128_f32[2];
	}
}
void Render::Geometries::TransformGeometries(DirectX::XMFLOAT3 Translation)
{
	this->m_PosOrigin.x += Translation.x;
	this->m_PosOrigin.y += Translation.y;
	this->m_PosOrigin.z += Translation.z;
}
void Render::Geometries::TransformGeometries(DirectX::XMMATRIX MatrixTranslation)
{
	DirectX::XMVECTOR d = MatrixTranslation.r[3];

	this->m_PosOrigin.x += d.m128_f32[0];
	this->m_PosOrigin.y += d.m128_f32[1];
	this->m_PosOrigin.z += d.m128_f32[2];
	
}
void Render::Geometries::TransformGeometries(DirectX::XMMATRIX Rotation)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			this->m_rotation.r[i].m128_f32[j] *= Rotation.r[i].m128_f32[j];	
}

#pragma endregion


DirectX::XMMATRIX Render::Geometries::GetRotationMatrix()
{
	return this->m_rotation;
}
DirectX::XMFLOAT3 Render::Geometries::GetPosOrigin()
{
	return this->m_PosOrigin;
}

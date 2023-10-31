#pragma once
#include<DirectXMath.h>
#include<DirectXPackedVector.h>
struct TRANSFORM {
	DirectX::XMMATRIX mRot ;
	DirectX::XMFLOAT3 vScale{ 1,1,1 };
	DirectX::XMFLOAT3 vTranslation = { 0,0,0 };
};
struct Vertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};

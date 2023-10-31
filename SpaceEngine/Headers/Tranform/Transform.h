#pragma once
#include<DirectXMath.h>
#include<DirectXPackedVector.h>
#define MAX_POINT 10 
#define NULLXMFLOAT3 DirectX::XMFLOAT3{NULL, NULL, NULL}
#define NULLVERTEX Vertex{{NULL, NULL, NULL},{ NULL,NULL,NULL,NULL }}
#define NULLMATRIX DirectX::XMMATRIX{{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}


struct TRANSFORM {
	DirectX::XMMATRIX mRot = NULLMATRIX;
	DirectX::XMFLOAT3 vScale = NULLXMFLOAT3;
	DirectX::XMFLOAT3 vTranslation = NULLXMFLOAT3;
};
struct Vertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};

#pragma once
#include<DirectXMath.h>
#include<DirectXPackedVector.h>
#define MAX_POINT 10 
#define NULLXMFLOAT3 DirectX::XMFLOAT3{NULL, NULL, NULL}
#define NULLVERTEX Vertex{{NULL, NULL, NULL},{ NULL,NULL,NULL,NULL }}
#define NULLMATRIX DirectX::XMMATRIX{{NULL,NULL,NULL,NULL},{NULL,NULL,NULL,NULL},{NULL,NULL,NULL,NULL},{NULL,NULL,NULL,NULL}}


struct TRANSFORM {
	DirectX::XMFLOAT3 vScale = NULLXMFLOAT3;
	DirectX::XMMATRIX mScale = NULLMATRIX;

	DirectX::XMFLOAT3 vTranslation = NULLXMFLOAT3;
	DirectX::XMMATRIX mTranslation = NULLMATRIX;
	DirectX::XMMATRIX mRot = NULLMATRIX;
};
struct Vertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};
struct OrderDraw
{
	float DrawOrder[3] = { NULL,NULL,NULL };
};
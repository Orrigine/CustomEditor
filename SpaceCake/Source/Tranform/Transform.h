#pragma once
#include "Headers/pch.h"

struct TRANSFORM {
	DirectX::XMFLOAT3 vScale;
	DirectX::XMMATRIX mScale;

	DirectX::XMFLOAT3 vTranslation;
	DirectX::XMMATRIX mTranslation;

	DirectX::XMFLOAT4 qRot;
	DirectX::XMMATRIX mRot;


	DirectX::XMFLOAT3 vOrigin;
	DirectX::XMMATRIX mOrigin;
};
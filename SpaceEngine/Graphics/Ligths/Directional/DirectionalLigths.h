#pragma once
#include "Graphics/Ligths/GlobalLigths.h"
#include"Engine/Entity.cpp"

class DirectionalLigths : public GlobalLigths
{
private:
	DirectX::XMVECTOR Direction = { 0,0,0 };
	DirectX::XMFLOAT3 Position;
	float precision; // Min: 0, Max: 1
public:

	DirectionalLigths(DirectX::XMFLOAT3 position,float intensity , float precision, DirectX::XMVECTOR dir);
	~DirectionalLigths ();
	void changeDirection(DirectX::XMVECTOR newDirection);
	void changePrecision(float newprecision);
};


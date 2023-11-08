#pragma once
#include "Graphics/Ligths/GlobalLigths.h"
#include"Engine/Entity.cpp"

class DirectionalLigths : public GlobalLigths
{
private:
	SpaceEngine::Vector3f Direction = { 0,0,0 };
	DirectX::XMFLOAT3 Position;
	float precision; // Min: 0, Max: 1
public:

	DirectionalLigths(DirectX::XMFLOAT3 position,float intensity , float precision, SpaceEngine::Vector3f);
	~DirectionalLigths ();
	SpaceEngine::Vector3f Normalize(SpaceEngine::Vector3f dir);
	void changeDirection(SpaceEngine::Vector3f newDirection);
	void changePrecision(float newprecision);
	DirectX::XMFLOAT3 getPosition();
	SpaceEngine::Vector3f getDirection();
	float getPrecision();
	bool Verify(SpaceEngine::Vector3f, float );
};


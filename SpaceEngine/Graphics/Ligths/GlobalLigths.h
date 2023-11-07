#pragma once
#include "Engine/Component/IComponent.hpp"
#include<DirectXMath.h>
#include <string>

class GlobalLigths
{
protected:
	DirectX::XMFLOAT4 color;
	float intensity;

public:
	GlobalLigths();
	~GlobalLigths();
	void init(DirectX::XMFLOAT4 newcolor , float newIntencity);
	void changeColor(DirectX::XMFLOAT4 color);
	void changeintencity(float newIntencity);
	float getIntensity();
};


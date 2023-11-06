#pragma once
#include "Engine/Component/IComponent.hpp"
#include<DirectXMath.h>
#include <string>

class GlobalLigths
{
protected:
	DirectX::XMFLOAT4 color;
	std::string* filenameShader;
	float intensity;

public:
	GlobalLigths(DirectX::XMFLOAT4 color, std::string* filenameShader, float intensity);
	~GlobalLigths();
	void changeColor(DirectX::XMFLOAT4 color);
	void changeShader(std::string* newFilename);
	void changeintencity(float newIntencity);
};


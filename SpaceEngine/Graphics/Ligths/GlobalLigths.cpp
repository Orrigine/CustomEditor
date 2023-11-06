#include "GlobalLigths.h"



GlobalLigths::GlobalLigths(DirectX::XMFLOAT4 color, std::string* filenameShader, float intensity)
{
	this->color = color;
	this->filenameShader = filenameShader;
	this->intensity = intensity;
}

GlobalLigths::~GlobalLigths()
{
}

void GlobalLigths::changeColor(DirectX::XMFLOAT4 color)
{
	this->color = color;
}

void GlobalLigths::changeShader(std::string* newFilename)
{
	this->filenameShader = newFilename;
}

void GlobalLigths::changeintencity(float newIntencity)
{
	this->intensity = newIntencity;
}


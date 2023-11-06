#include "GlobalLigths.h"
GlobalLigths::GlobalLigths()
{
}
GlobalLigths::~GlobalLigths()
{
}

void GlobalLigths::init(DirectX::XMFLOAT4 newcolor, float newIntencity)
{
	this->color = newcolor;
	this->intensity = newIntencity;
}
void GlobalLigths::changeColor(DirectX::XMFLOAT4 color)
{
	this->color = color;
}
void GlobalLigths::changeintencity(float newIntencity)
{
	this->intensity = newIntencity;
}


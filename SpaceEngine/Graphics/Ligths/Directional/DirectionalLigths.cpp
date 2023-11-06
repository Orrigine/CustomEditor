#include"DirectionalLigths.h"

DirectionalLigths::DirectionalLigths(DirectX::XMFLOAT3 position, float intensity, float precision, DirectX::XMVECTOR dir)
{
	this->Position = position;
	this->intensity = intensity;
	this->precision = std::max(0.f,std::min(precision,1.f));
	this->Direction = dir;
}
DirectionalLigths ::~DirectionalLigths()
{
}

void DirectionalLigths::changeDirection(DirectX::XMVECTOR newDirection)
{
	this->Direction = newDirection;
}
void DirectionalLigths::changePrecision(float newPrecisioon) {
	this->precision = std::max(0.f, std::min(newPrecisioon, 1.f));
}

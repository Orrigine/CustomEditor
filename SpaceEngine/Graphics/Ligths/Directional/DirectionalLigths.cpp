#include"DirectionalLigths.h"

DirectionalLigths::DirectionalLigths(DirectX::XMFLOAT3 position, float intensity, float precision, DirectX::XMVECTOR dir)
{
	this->Position = position;
	this->intensity = intensity;
	this->precision = (0.f > (precision<1.f)?precision : 1.f ) ? 0.f : (precision < 1.f) ? precision : 1.f;
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
	this->precision = (0.f > (precision < 1.f) ? precision : 1.f) ? 0.f : (precision < 1.f) ? precision : 1.f;
}

DirectX::XMFLOAT3 DirectionalLigths::getPosition()
{
	return this->Position;
}



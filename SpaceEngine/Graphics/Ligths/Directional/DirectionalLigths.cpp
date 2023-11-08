#include"DirectionalLigths.h"

DirectionalLigths::DirectionalLigths(DirectX::XMFLOAT3 position, float intensity, float precision, SpaceEngine::Vector3f dir)
{
	this->Position = position;
	this->intensity = intensity;
	this->precision = (0.f > (precision < 1.f) ? precision : 1.f) ? 0.f : (precision < 1.f) ? precision : 1.f;
	this->Direction = dir;
}
DirectionalLigths ::~DirectionalLigths()
{
}

SpaceEngine::Vector3f DirectionalLigths::Normalize(SpaceEngine::Vector3f dir)
{
	float divide = std::sqrt((float)std::pow(dir.x + dir.x, 2) + (float)std::pow(dir.y + dir.y, 2) + (float)std::pow(dir.z + dir.z, 2));
	SpaceEngine::Vector3f newDir = { dir.x / divide ,dir.y / divide ,dir.z / divide };
	return newDir;
}

void DirectionalLigths::changeDirection(SpaceEngine::Vector3f newDirection)
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

SpaceEngine::Vector3f DirectionalLigths::getDirection()
{
	return this->Direction;
}

float DirectionalLigths::getPrecision()
{
	return this->precision;
}

bool DirectionalLigths::Verify(SpaceEngine::Vector3f posEntity, float distance)
{
	DirectX::XMFLOAT3 posLigth = this->getPosition();
	float precision = this->getPrecision();
	SpaceEngine::Vector3f normalizePosEntity = this->Normalize(posEntity);

	if (distance < intensity)
		if ( this->Direction.x - std::cos(precision) < normalizePosEntity.x &&  normalizePosEntity.x< this->Direction.x + std::cos(precision))
			if ( this->Direction.y - std::cos(precision) < normalizePosEntity.y &&  normalizePosEntity.y< this->Direction.y + std::cos(precision))
				if ( this->Direction.z - std::cos(precision) < normalizePosEntity.z &&  normalizePosEntity.z< this->Direction.z + std::cos(precision))
					return true;	
	return false;
}



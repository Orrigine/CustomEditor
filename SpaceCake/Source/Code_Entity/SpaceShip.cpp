#include"SpaceShip.h"

SpaceShip::SpaceShip(SpaceEngine::Engine* Engine)
{
	this->m_Engine = Engine;
	this->m_SpaceShipEntity = this->m_Engine->createEntity("SpaceShip");

	this->m_Transform = this-> m_SpaceShipEntity-> getComponent<SpaceEngine::Transform>();
	this->m_SpaceShipMesh = this->m_SpaceShipEntity->addComponent<SpaceEngine::BoxMesh>();

	this->m_Transform ->setPosition({ 0, 0, 0 });
	this->m_Transform ->setScale({ 3, 0.5, 2 });

	this->m_Transform = this->m_SpaceShipEntity->getComponent<SpaceEngine::Transform>();
	this->m_SpaceShipMesh = this->m_SpaceShipEntity->addComponent<SpaceEngine::BoxMesh>();

	this->m_Transform->setPosition({ 1, 0, 0 });
	this->m_Transform->setScale({0.5, 3, 2 });
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::Update()
{

}

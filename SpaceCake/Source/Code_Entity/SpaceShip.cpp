#include"SpaceShip.h"

SpaceShip::SpaceShip(SpaceEngine::Scene Scene)
{
	this -> m_Scene = &Scene;
	this -> m_SpaceShipEntity = this->m_Scene->createEntity("SpaceShip");
	this -> m_Transform =  &this-> m_SpaceShipEntity-> getComponent<SpaceEngine::Transform>();
	this -> m_Transform ->setPosition({ 0, 1, 0 });
}

SpaceShip::~SpaceShip()
{

}
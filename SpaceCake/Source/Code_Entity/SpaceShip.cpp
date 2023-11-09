#include"SpaceShip.h"

SpaceShip::SpaceShip(SpaceEngine::Engine* Engine)
{
	this->m_Engine = Engine;
	Create();
	
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::Create()
{/*
	//First Shape 
	std::shared_ptr<SpaceEngine::Entity>m_SpaceShipEntity = this->m_Engine->createEntity("1");

	std::shared_ptr<SpaceEngine::Transform>m_Transform = m_SpaceShipEntity->getComponent<SpaceEngine::Transform>();
	std::shared_ptr<SpaceEngine::BoxMesh>m_SpaceShipMeshBox = m_SpaceShipEntity->addComponent<SpaceEngine::BoxMesh>();

	m_Transform->setPosition({ 0, 0, 0 });
	m_Transform->setScale({ 3, 0.5, 2 });
	//Second Shape 
	m_SpaceShipEntity = this->m_Engine->createEntity("2");


	m_Transform = m_SpaceShipEntity->getComponent<SpaceEngine::Transform>();
	m_SpaceShipMeshBox = m_SpaceShipEntity->addComponent<SpaceEngine::BoxMesh>();

	m_Transform->setPosition({ 3, 0, 0 });
	m_Transform->setScale({ 0.5, 3, 2 });
	//Third Shape 
	m_SpaceShipEntity = this->m_Engine->createEntity("3");


	m_Transform = m_SpaceShipEntity->getComponent<SpaceEngine::Transform>();
	m_SpaceShipMeshBox =m_SpaceShipEntity->addComponent<SpaceEngine::BoxMesh>();

	m_Transform->setPosition({ -3, 0, 0 });
	m_Transform->setScale({ 0.5, 3, 2 });
	m_Transform->setRotation({ 90,045,25 });

	//Shape 4 
	m_SpaceShipEntity = this->m_Engine->createEntity("3");
	 

	m_Transform = m_SpaceShipEntity->getComponent<SpaceEngine::Transform>();
	std::shared_ptr<SpaceEngine::SphereMesh>m_SpaceShipMeshSphere = m_SpaceShipEntity->addComponent<SpaceEngine::SphereMesh>();

	m_Transform->setPosition({ 0, 0, 0 });
	m_Transform->setScale({ 1, 1, 1 });
	*/
}

void SpaceShip::Update()
{

}

SpaceEngine::Vector3f SpaceShip::GetPos()
{
	return this->m_Pos;
}

void SpaceShip::Move(SpaceEngine::Vector3f pos)
{
	this->m_Pos = { this->m_Pos.x + pos.x ,this->m_Pos.y + pos.y, this->m_Pos.z + pos.z };
}

void SpaceShip::Fire()
{
	for (int i = 0; i < this->m_Engine->getEntities().size(); i++) {
		std::shared_ptr<SpaceEngine::Entity> OneEntity = this->m_Engine->getEntities()[i];
		std::shared_ptr<SpaceEngine::Transform> OneEntityTransform =OneEntity->getComponent<SpaceEngine::Transform>();
	
		SpaceEngine::Vector3f a =OneEntityTransform->getPosition();
		SpaceEngine::Vector3f b = OneEntityTransform->getScale();
	
	}
}

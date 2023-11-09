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
{
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
	m_Transform->setRotation({ 0,90,0 });

	//Shape 4 
	m_SpaceShipEntity = this->m_Engine->createEntity("3");
	 

	m_Transform = m_SpaceShipEntity->getComponent<SpaceEngine::Transform>();
	std::shared_ptr<SpaceEngine::SphereMesh>m_SpaceShipMeshSphere = m_SpaceShipEntity->addComponent<SpaceEngine::SphereMesh>();

	m_Transform->setPosition({ 0, 0, 0 });
	m_Transform->setScale({ 1, 1, 1 });
}

void SpaceShip::Update()
{

}

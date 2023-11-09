#include"Headers/pch.h"

class SpaceShip
{
public:
	SpaceShip(SpaceEngine::Engine* Scene);
	~SpaceShip();
	void Update();

private:
	SpaceEngine::Engine* m_Engine;
	std::shared_ptr<SpaceEngine::Transform> m_Transform ; 
	std::shared_ptr<SpaceEngine::BoxMesh> m_SpaceShipMesh;  //A revoir 
	std::shared_ptr<SpaceEngine::Entity> m_SpaceShipEntity;

};


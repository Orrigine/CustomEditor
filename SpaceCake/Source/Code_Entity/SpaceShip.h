#include"Headers/pch.h"

class SpaceShip
{
public:
	SpaceShip(SpaceEngine::Scene Scene);
	~SpaceShip();

private:
	SpaceEngine::Scene* m_Scene;
	std::shared_ptr<SpaceEngine::Transform>* m_Transform ; 
	std::shared_ptr<SpaceEngine::Entity> m_SpaceShipEntity;

};


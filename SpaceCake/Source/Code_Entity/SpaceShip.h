#include"Headers/pch.h"

class SpaceShip
{
public:
	SpaceShip(SpaceEngine::Engine* Scene);
	~SpaceShip();


	void Create();
	void Update();
	SpaceEngine::Vector3f GetPos();
	void Move(SpaceEngine::Vector3f );
	void Fire();

private:
	SpaceEngine::Engine* m_Engine;  //A revoir 
	SpaceEngine::Vector3f m_Pos;

};


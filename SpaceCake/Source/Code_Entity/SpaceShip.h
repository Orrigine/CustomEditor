#include"Headers/pch.h"

class SpaceShip
{
public:
	SpaceShip(SpaceEngine::Engine* Scene);
	~SpaceShip();
	void Create();
	void Update();

private:
	SpaceEngine::Engine* m_Engine;  //A revoir 
	

};


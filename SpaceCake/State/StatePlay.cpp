#include "StatePlay.h"

StatePlay *StatePlay::_instance = nullptr;

StatePlay::StatePlay()
{
}

StatePlay::~StatePlay()
{
}

void StatePlay::enter()
{
}

void StatePlay::toggle()
{
}

void StatePlay::exit()
{
}

StatePlay *StatePlay::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new StatePlay();
    }
    return _instance;
}

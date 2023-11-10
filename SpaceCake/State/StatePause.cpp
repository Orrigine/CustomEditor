#include "StatePause.h"

StatePause *StatePause::_instance = nullptr;

StatePause::StatePause()
{
    enter();
}

StatePause::~StatePause()
{
}

void StatePause::enter()
{
    // TODO: STOP THE TIME
}

void StatePause::toggle()
{
}

void StatePause::exit()
{
    // TODO: RESUME THE TIME
}

StatePause *StatePause::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new StatePause();
    }
    return _instance;
}

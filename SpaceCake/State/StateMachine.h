#pragma once
#include "State.h"
#include <memory>

class StateMachine
{

public:
    StateMachine();
    ~StateMachine();

    inline State *getCurrentState() const { return _currentState; }

    void setState(State &newState);

    void toggle();

    static std::shared_ptr<StateMachine> getInstance();

private:
    static std::shared_ptr<StateMachine> _instance;

    State *_currentState;
    State *_nextState; // Usefull for scene transitions
};

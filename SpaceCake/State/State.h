#pragma once

class StateMachine;

class State
{

public:
    virtual void enter() = 0;
    virtual void toggle() = 0;
    virtual void exit() = 0;

    ~State(){};
};

#pragma once

#include "State.h"

class StatePlay : public State
{
public:
    StatePlay(/* args */);
    ~StatePlay();

    virtual void enter() override;
    virtual void toggle() override;
    virtual void exit() override;

public:
    static StatePlay *getInstance();

private:
    // Singleton
    static StatePlay *_instance;
};

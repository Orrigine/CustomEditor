#pragma once
#include "State.h"

class StatePause : public State
{
public:
    StatePause(/* args */);
    ~StatePause();

    virtual void enter() override;
    virtual void toggle() override;
    virtual void exit() override;

public:
    static StatePause *getInstance();

private:
    // Singleton
    static StatePause *_instance;
};

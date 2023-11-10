#pragma once

#include "State.h"

class StateMainMenu : public State
{
public:
    virtual void enter() override;
    virtual void toggle() override;
    virtual void exit() override;

    StateMainMenu(/* args */);
    ~StateMainMenu();

public:
    static StateMainMenu *getInstance();

private:
    // Singleton
    static StateMainMenu *_instance;
};

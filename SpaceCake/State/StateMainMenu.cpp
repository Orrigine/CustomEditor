#include "StateMainMenu.h"

StateMainMenu *StateMainMenu::_instance = nullptr;

StateMainMenu::StateMainMenu()
{
    enter();
}

void StateMainMenu::enter()
{
}

void StateMainMenu::toggle()
{
}

void StateMainMenu::exit()
{
}

StateMainMenu::~StateMainMenu()
{
}

StateMainMenu *StateMainMenu::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new StateMainMenu();
    }
    return _instance;
}

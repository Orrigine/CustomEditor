#include "StateMachine.h"
#include "State/StateMainMenu.h"
#include "State/StatePlay.h"
#include "State/StatePause.h"

std::shared_ptr<StateMachine> StateMachine::_instance = nullptr;

StateMachine::StateMachine()
{
    // FIXME: for now it's play state at beginning
    _currentState = StatePlay::getInstance();
    _nextState = nullptr;

    _instance = nullptr;
}

StateMachine::~StateMachine()
{
    // Assume if we are deleting the state machine,
    // we are exiting the game
    delete _currentState;
    delete _nextState;

    StateMainMenu::getInstance()->~StateMainMenu();
    StatePlay::getInstance()->~StatePlay();
    StatePause::getInstance()->~StatePause();
}

void StateMachine::setState(State &newState)
{
    _currentState->exit();
    _currentState = &newState;
    _currentState->enter();
}

void StateMachine::toggle()
{
    // Not really important to toggle states manually
    // use -_currentState->toggle() directly in the enter() for automatic toggling
    _currentState->toggle();
}

std::shared_ptr<StateMachine> StateMachine::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = std::make_shared<StateMachine>();
    }

    return _instance;
}

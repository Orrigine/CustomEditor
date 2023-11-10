#include "Engine.h"
#include "State/StateMachine.h"
// #include "Engine/Core/Core.h"

#include <memory>

class Game
{
public:
    Game(SpaceEngine::Engine engine);
    ~Game();

    void init();
    void run();

    static std::shared_ptr<Game> GetInstance();

    // gettor for the state machine

    static std::shared_ptr<StateMachine> _stateMachine;
private:
    static std::shared_ptr<Game> _instance;
    SpaceEngine::Engine _engine;

    bool _isRunning;
};

#include "Engine.h"
//#include "Engine/Core/Core.h"
#include <time.h>
#include <memory>
#include <cstdlib>

class Game
{
public:
    Game(SpaceEngine::Engine engine);
    ~Game();

    void init();
    void run();
    void createCrates(int nb);

    static std::shared_ptr<Game> GetInstance();

private:
    static std::shared_ptr<Game> _instance;
    SpaceEngine::Engine _engine;

    bool _isRunning;
};

#pragma once
#include "Game.h"
#include <functional>

class Application {
    Application() = default;
    Game game;
public:
    static Application& getInstance();
    void run();
};

#pragma once
#include "Game.h"

class Application {
    Application() = default;
    Game game;
public:
    static Application& getInstance();
    void run();
};

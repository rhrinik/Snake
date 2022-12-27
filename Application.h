#pragma once
#include "Graphics.h"
#include "Game.h"

class Application {
    Application() : game(gfx) {}
    Graphics gfx;
    Game game;
    bool isRunning{true};
    static constexpr std::size_t windowWidth = 800;
    static constexpr std::size_t windowHeight = 600;
public:
    static Application& getInstance();
    void run();
};

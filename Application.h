#pragma once
#include "Graphics.h"
#include "Game.h"

class Application {
    Application() : game(gfx) {}
    Graphics gfx;
    Game game;
    bool isRunning{true};
    static constexpr std::string_view windowTitle = "Snake";
public:
    static Application& getInstance();
    void run();
};

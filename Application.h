#pragma once
#include "Game.h"

class Application {
    Application() = default;
    Game game;
    static constexpr std::size_t windowWidth = 800;
    static constexpr std::size_t windowHeight = 600;
public:
    static Application& getInstance();
    void run();
};

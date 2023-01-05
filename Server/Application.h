#pragma once
#include "Game.h"
#include <functional>

class Application {
    Application() = default;
    Game game;
    static std::pair<bool, int> checkPort(int argc, char *argv[]);
    std::jthread userInput;
public:
    static Application& getInstance();
    void run(int argc, char *argv[]);
};

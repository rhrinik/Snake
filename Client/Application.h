#pragma once
#include "Graphics.h"
#include "Game.h"

class Application {
    Application() : gfx(wnd), game(wnd,gfx) {}
    Window wnd;
    Graphics gfx;
    Game game;
    static std::size_t constexpr windowWidth = 2000;
    static std::size_t constexpr windowHeight = 1500;
    static std::string_view constexpr windowTitle = "Snake";
public:
    static Application& getInstance();
    void run();
};

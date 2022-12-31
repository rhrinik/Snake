#pragma once
#include "Display/Graphics.h"
#include "GameStates/GameState.h"
#include "GameStates/GameStatePlaying.h"
#include "GameStates/GameStateDummy.h"
#include "GameStates/GameStateMenu.h"

class Game {
    Graphics& gfx;
    Window &wnd;
public:
    explicit Game(Window &wnd, Graphics &gfx) : wnd(wnd), gfx(gfx) {}
    void run();
    void init();
    std::vector<std::unique_ptr<GameState>> states;
    GameState::States currentState{GameState::Menu};
    GameState::States previousState{GameState::Start};
};

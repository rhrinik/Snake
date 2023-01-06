#pragma once
#include <memory>
#include "Display/Graphics.h"
#include "GameStates/GameState.h"
#include "GameStates/GameStatePlaying.h"
#include "GameStates/GameStateDummy.h"
#include "GameStates/GameStateMenu.h"
#include "GameStates/GameStateLose.h"
#include "GameStates/GameStateWin.h"
#include "GameStates/GameStateDraw.h"
#include "GameStates/GameStateSelectIPAndPort.h"

class Game {
    Graphics& gfx;
    Window &wnd;
    Server server;
public:
    explicit Game(Window &wnd, Graphics &gfx) : wnd(wnd), gfx(gfx) {}
    void run();
    void init();
    std::vector<std::shared_ptr<GameState>> states;
    GameState::States currentState{GameState::Menu};
    GameState::States previousState{GameState::Start};
};

#include "Game.h"

void Game::run() {
    while (currentState != GameState::End) {
        auto const prev = previousState;
        previousState = currentState;
        currentState = states[static_cast<int>(currentState)]->run(prev);
    }
}

void Game::init() {
    states.emplace_back(std::make_shared<GameStateDummy>(wnd,gfx));
    states.emplace_back(std::make_shared<GameStateDummy>(wnd,gfx));
    states.emplace_back(std::make_shared<GameStatePlaying>(wnd,gfx,server));
    auto menu = std::make_shared<GameStateMenu>(wnd,gfx);
    states.emplace_back(menu);
    states.emplace_back(std::make_shared<GameStateLose>(wnd,gfx));
    states.emplace_back(std::make_shared<GameStateWin>(wnd,gfx));
    states.emplace_back(std::make_shared<GameStateDraw>(wnd,gfx));
    states.emplace_back(std::make_shared<GameStateSelectIPAndPort>(wnd,gfx,menu,server));
}
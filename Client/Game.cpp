#include "Game.h"

void Game::run() {
    while (currentState != GameState::End) {
        auto const prev = previousState;
        previousState = currentState;
        currentState = states[static_cast<int>(currentState)]->run(prev);
    }
}

bool Game::init() {
    states.emplace_back(std::make_unique<GameStateDummy>(wnd,gfx));
    states.emplace_back(std::make_unique<GameStateDummy>(wnd,gfx));
    states.emplace_back(std::make_unique<GameStatePlaying>(wnd,gfx));
    states.emplace_back(std::make_unique<GameStateMenu>(wnd,gfx));
    return running = true;
}

bool Game::isRunning() const {
    return running;
}

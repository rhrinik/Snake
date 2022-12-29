#include "Game.h"

void Game::run() {
    while (currentState != GameState::End) {
        if (currentState != previousState)
            states[static_cast<int>(currentState)]->init();
        previousState = currentState;
        currentState = states[static_cast<int>(currentState)]->run(gfx);
    }
}

bool Game::init() {
    states.emplace_back(std::make_unique<GameStateDummy>());
    states.emplace_back(std::make_unique<GameStateDummy>());
    states.emplace_back(std::make_unique<GameStatePlaying>());
    states.emplace_back(std::make_unique<GameStateMenu>());
    return running = true;
}

bool Game::isRunning() const {
    return running;
}

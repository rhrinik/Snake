#include "Game.h"

void Game::run() {
    while (currentState != ServerState::End) {
        auto const prev = previousState;
        previousState = currentState;
        currentState = states[static_cast<int>(currentState)]->run(prev);
    }
}

void Game::init() {
    states.emplace_back(std::make_unique<ServerStateWaitingForPlayers>(clients));
    states.emplace_back(std::make_unique<ServerStatePlayingGame>(clients));
}

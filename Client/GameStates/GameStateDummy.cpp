#include "GameStateDummy.h"

GameState::States GameStateDummy::runState(States previous) {
    return End;
}

GameState::States GameStateDummy::updateState() {
    return End;
}

void GameStateDummy::drawState() {
}

void GameStateDummy::initState() {
}

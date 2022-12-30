#include "GameStateDummy.h"

GameState::States GameStateDummy::runState(States previous) {
    return End;
}

void GameStateDummy::updateState() {
}

void GameStateDummy::drawState() {
}

void GameStateDummy::initState() {
}

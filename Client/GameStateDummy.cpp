#include "GameStateDummy.h"

GameState::States GameStateDummy::runState(Graphics &gfx) {
    return End;
}

void GameStateDummy::updateState() {
}

void GameStateDummy::drawState(Graphics &gfx) {
}

void GameStateDummy::initState() {
}

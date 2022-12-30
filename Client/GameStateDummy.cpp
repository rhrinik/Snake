#include "GameStateDummy.h"

GameState::States GameStateDummy::runState(Window &wnd, Graphics &gfx) {
    return End;
}

void GameStateDummy::updateState(Window &wnd) {
}

void GameStateDummy::drawState(Graphics &gfx) {
}

void GameStateDummy::initState() {
}

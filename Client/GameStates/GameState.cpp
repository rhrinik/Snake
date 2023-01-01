#include "GameState.h"

GameState::States GameState::run(States previous) {
    wnd.processEvents();
    return runState(previous);
}

GameState::States GameState::update() {
    return updateState();
}

void GameState::draw() {
    gfx.beginFrame();
    drawState();
    gfx.endFrame();
}

void GameState::init() {
    initState();
}

#include "GameState.h"

GameState::States GameState::run(States previous) {
    wnd.processEvents();
    return runState(previous);
}

void GameState::update() {
    updateState();
}

void GameState::draw() {
    gfx.beginFrame();
    drawState();
    gfx.endFrame();
}

void GameState::init() {
    initState();
}

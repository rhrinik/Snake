#include "GameState.h"

GameState::States GameState::run() {
    wnd.processEvents();
    return runState();
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

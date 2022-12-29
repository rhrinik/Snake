#include "GameState.h"

GameState::States GameState::run(Graphics &gfx) {
    gfx.processEvents();
    return runState(gfx);
}

void GameState::update() {
    updateState();
}

void GameState::draw(Graphics &gfx) {
    gfx.beginFrame();
    drawState(gfx);
    gfx.endFrame();
}

void GameState::init() {
    initState();
}

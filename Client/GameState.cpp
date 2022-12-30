#include "GameState.h"

GameState::States GameState::run(Window &wnd, Graphics &gfx) {
    wnd.processEvents();
    return runState(wnd, gfx);
}

void GameState::update(Window &wnd) {
    updateState(wnd);
}

void GameState::draw(Graphics &gfx) {
    gfx.beginFrame();
    drawState(gfx);
    gfx.endFrame();
}

void GameState::init() {
    initState();
}

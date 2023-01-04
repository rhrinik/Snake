#include "GameStateWin.h"

void GameStateWin::initState() {
    nextState = Lose;
    loseImage.loadFromFile("../Client/Resources/img.png");
}

GameState::States GameStateWin::runState(GameState::States previous) {
    if (previous == Playing)
        init();

    draw();
    return nextState;
}

GameState::States GameStateWin::updateState() {
    return Lose;
}

void GameStateWin::drawState() {
    gfx.drawImage(loseImage);
}

void GameStateWin::onKeyEnter() {
    nextState = Menu;
}
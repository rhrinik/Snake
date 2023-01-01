#include "GameStateLose.h"

void GameStateLose::initState() {
    nextState = Lose;
    loseImage.loadFromFile("../Client/Resources/img.png");
}

GameState::States GameStateLose::runState(GameState::States previous) {
    if (previous == Playing)
        init();

    draw();
    return nextState;
}

GameState::States GameStateLose::updateState() {
    return Lose;
}

void GameStateLose::drawState() {
    gfx.drawImage(loseImage);
}

void GameStateLose::onKeyEnter() {
    nextState = Menu;
}
#include "GameStateLose.h"

void GameStateLose::initState() {
    nextState = Lose;
    loseImage.loadFromFile("../Client/Resources/img.png");
}

GameState::States GameStateLose::runState(GameState::States previous) {
    if (wnd.isWindowClosed())
        return End;
    if (previous == Playing)
        init();

    update();
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
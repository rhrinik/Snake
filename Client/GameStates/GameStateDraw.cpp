#include "GameStateDraw.h"

void GameStateDraw::initState() {
    nextState = Draw;
    font.loadFontFromFile("../Client/Resources/font.otf");

    title.setFont(font);
    title.setText("DRAW");
    title.setSize(300);
    std::pair<int,int> titlePosition = (wnd.getSize() - title.getSize()) / 2;
    title.setPosition(titlePosition);
}

GameState::States GameStateDraw::runState(GameState::States previous) {
    if (previous == Playing)
        init();

    draw();
    return nextState;
}

GameState::States GameStateDraw::updateState() {
    return Draw;
}

void GameStateDraw::drawState() {
    gfx.drawText(title);
}

void GameStateDraw::onKeyEnter() {
    nextState = Menu;
}
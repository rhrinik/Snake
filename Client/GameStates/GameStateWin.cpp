#include "GameStateWin.h"

void GameStateWin::initState() {
    nextState = Win;
    if (!init) {
        font.loadFontFromFile("../Client/Resources/font.otf");

        title.setFont(font);
        title.setText("YOU WIN!");
        title.setSize(300);
        std::pair<int, int> titlePosition = (wnd.getSize() - title.getSize()) / 2;
        title.setPosition(titlePosition);
    }
}

GameState::States GameStateWin::runState(GameState::States previous) {
    if (previous == Playing)
        init();

    draw();
    return nextState;
}

GameState::States GameStateWin::updateState() {
    return Win;
}

void GameStateWin::drawState() {
    gfx.drawText(title);
}

void GameStateWin::onKeyEnter() {
    nextState = Menu;
}
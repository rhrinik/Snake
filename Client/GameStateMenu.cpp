#include "GameStateMenu.h"

GameState::States GameStateMenu::runState() {
    if (wnd.isWindowClosed())
        return GameState::End;

    update();
    draw();

    return Menu;
}

void GameStateMenu::updateState() {
}

void GameStateMenu::drawState() {
    gfx.drawImage(imageBackground);
    gfx.drawText(menuTitle);
}

void GameStateMenu::initState() {
    imageBackground.loadFromFile("../Client/Resources/dark-grey-background-texture.jpg");

    font.loadFontFromFile("../Client/Resources/font.otf");

    menuTitle.setFont(font);
    menuTitle.setText("SNAKE");
    menuTitle.setSize(300);
    std::pair<int,int> menuTitlePosition = (wnd.getSize() - menuTitle.getSize())/2;
    menuTitlePosition.second -= wnd.getSize().second/4;
    menuTitle.setPosition(menuTitlePosition);
}

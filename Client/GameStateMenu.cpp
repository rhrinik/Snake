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

    menuTitle.loadFontFromFile("../Client/Resources/font.otf");
    menuTitle.setText("SNAKE");
    menuTitle.setPosition({20,20});
    menuTitle.setSize(40);
}

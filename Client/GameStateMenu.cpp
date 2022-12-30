#include "GameStateMenu.h"

GameState::States GameStateMenu::runState(Window &wnd, Graphics &gfx) {
    if (wnd.isWindowClosed())
        return GameState::End;

    update(wnd);
    draw(gfx);

    return Menu;
}

void GameStateMenu::updateState(Window &wnd) {
}

void GameStateMenu::drawState(Graphics &gfx) {
    gfx.drawImage(imageBackground);
    gfx.drawText(menuTitle);
}

void GameStateMenu::initState() {
    imageBackground.loadFromFile("../Client/Resources/dark-grey-background-texture.jpg");
    menuTitle.loadFromFile("../Client/Resources/font.otf");
}

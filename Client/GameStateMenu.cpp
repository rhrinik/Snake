#include "GameStateMenu.h"

GameState::States GameStateMenu::runState(Graphics &gfx) {
    if (gfx.isWindowClosed())
        return GameState::End;

    update();
    draw(gfx);

    return Menu;
}

void GameStateMenu::updateState() {
}

void GameStateMenu::drawState(Graphics &gfx) {
    gfx.drawImage(imageBackground);
}

void GameStateMenu::initState() {
    imageBackground.loadFromFile("../dark-grey-background-texture.jpg");
}

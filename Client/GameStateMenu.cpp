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
    gfx.drawText(title);
    gfx.drawText(play);
    gfx.drawText(exit);
}

void GameStateMenu::initState() {
    imageBackground.loadFromFile("../Client/Resources/dark-grey-background-texture.jpg");

    font.loadFontFromFile("../Client/Resources/font.otf");

    title.setFont(font);
    title.setText("SNAKE");
    title.setSize(300);
    std::pair<int,int> titlePosition = (wnd.getSize() - title.getSize()) / 2;
    titlePosition.second -= wnd.getSize().second/4;
    title.setPosition(titlePosition);

    play.setFont(font);
    play.setText("Play");
    play.setSize(150);
    std::pair<int,int> playPosition = (wnd.getSize() - play.getSize()) / 2;
    play.setPosition(playPosition);

    exit.setFont(font);
    exit.setText("Exit");
    exit.setSize(150);
    std::pair<int,int> exitPosition = (wnd.getSize() - exit.getSize()) / 2;
    exitPosition.second += wnd.getSize().second/8;
    exit.setPosition(exitPosition);
}

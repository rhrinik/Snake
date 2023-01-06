#include "GameStateMenu.h"

GameState::States GameStateMenu::runState(States previous) {
    if (previous == Start)
        init();
    if (previous == Lose || previous == Win || previous == Draw) {
        restart();
    }

    auto state = update();
    draw();

    return state;
}

void GameStateMenu::restart() {
    selected = Play;
    input = true;
    selectionConfirmed = false;
}

GameState::States GameStateMenu::updateState() {
    if (selectionConfirmed)
        switch (selected) {
            case Play:
               // return Playing;
                input = false;
                return SelectIPAndPort;
            case Exit:
                return End;
        }
    return Menu;
}

void GameStateMenu::drawState() {
    gfx.drawImage(imageBackground,{1,1},{0,0});
    gfx.drawText(title);
    gfx.drawText(play);
    gfx.drawText(exit);
    switch (selected) {
        case Play:
            play.setOutlineSize(10);
            exit.setOutlineSize(0);
            break;
        case Exit:
            play.setOutlineSize(0);
            exit.setOutlineSize(10);
            break;
    }
}

void GameStateMenu::initState() {
    restart();
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
    play.setOutlineColor(Color(70,70,70));

    exit.setFont(font);
    exit.setText("Exit");
    exit.setSize(150);
    std::pair<int,int> exitPosition = (wnd.getSize() - exit.getSize()) / 2;
    exitPosition.second += wnd.getSize().second/8;
    exit.setPosition(exitPosition);
    exit.setOutlineColor(Color(70,70,70));
}

void GameStateMenu::onKeyUp() {
    if (!input)
        return;
    selected = Play;
}

void GameStateMenu::onKeyDown() {
    if (!input)
        return;
    selected = Exit;
}

void GameStateMenu::onKeyEnter() {
    if (!input)
        return;
    selectionConfirmed = true;
}

void GameStateMenu::drawAsBackGround() {
    drawState();
}

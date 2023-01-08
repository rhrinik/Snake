#include "GameStateTryToConnect.h"

GameState::States GameStateTryToConnect::runState(GameState::States previous) {
    if (previous == SelectIPAndPort && !initPass) {
        init();
        restart();
    } else if (previous != TryToConnect)
        restart();

    update();
    draw();
    return nextState;
}

GameState::States GameStateTryToConnect::updateState() {
    if (!server.isConnected() && tryConnectFor.removeTime(4)) {
        nextState = Menu;
        return Menu;
    }

    if (server.isConnected()) {
        connectionStatusText.setText("Waiting for other player to join...");
        auto data = server.receiveData();
        switch (data.first) {
            case sf::Socket::Done:
                if (data.second.getSnakeState() == DataFromServer::OtherReady)
                    nextState = Playing;
                break;
            case sf::Socket::Disconnected:
            case sf::Socket::Error:
                nextState = Menu;
                return Menu;
            case sf::Socket::NotReady:
            case sf::Socket::Partial:
                break;
        }
    } else {
        connectionStatusText.setText("Trying to connect to server...");
        if (server.connect())
            server.setConnected(true);
    }
    return Playing;
}

void GameStateTryToConnect::drawState() {
    menu->drawAsBackGround();
    gfx.drawText(connectionStatusText);
}

void GameStateTryToConnect::initState() {
    server.setConnected(false);
    initPass = true;
    input = true;
    nextState = TryToConnect;
    font.loadFontFromFile("../Client/Resources/font.otf");

    connectionStatusText.setFont(font);
    connectionStatusText.setText("Trying to connect to server...");
    connectionStatusText.setSize(30);
    std::pair<int,int> pipPosition = (wnd.getSize() - connectionStatusText.getSize()) / 2;
    connectionStatusText.setPosition(pipPosition + std::make_pair(0,wnd.getSize().second/3));
}

void GameStateTryToConnect::restart() {
    server.setConnected(false);
    tryConnectFor.reset();
    input = true;
    nextState = TryToConnect;
}

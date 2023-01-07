#include "GameStateSelectIPAndPort.h"

GameState::States GameStateSelectIPAndPort::runState(GameState::States previous) {
    if (previous == Menu && !initPass) {
        init();
        restart();
    } else if (previous != SelectIPAndPort)
        restart();

    draw();
    return nextState;
}

GameState::States GameStateSelectIPAndPort::updateState() {
    return SelectIPAndPort;
}

void GameStateSelectIPAndPort::drawState() {
    menu->drawAsBackGround();
    if (!ipSelected) {
        gfx.drawText(promptIp);
        gfx.drawText(inputIp);
    } else {
        gfx.drawText(promptPort);
        gfx.drawText(inputPort);
    }
}

void GameStateSelectIPAndPort::initState() {
    initPass = true;
    ipSelected = false;
    input = true;
    nextState = SelectIPAndPort;
    font.loadFontFromFile("../Client/Resources/font.otf");

    promptIp.setFont(font);
    promptIp.setText("Enter IP: ");
    promptIp.setSize(50);
    std::pair<int,int> pipPosition = (wnd.getSize() - promptIp.getSize()) / 2;
    pipPosition.first += wnd.getSize().second/4;
    promptIp.setPosition(pipPosition);

    promptPort.setFont(font);
    promptPort.setText("Enter Port: ");
    promptPort.setSize(50);
    std::pair<int,int> pPortPosition = (wnd.getSize() - promptPort.getSize()) / 2;
    pPortPosition.first += wnd.getSize().second/4;
    promptPort.setPosition(pPortPosition);

    inputIp.setFont(font);
    inputIp.setText("Enter IP: ");
    inputIp.setSize(50);
    inputIp.setPosition(pipPosition + std::make_pair(promptIp.getSize().first,0));
    inputIp.setText({});

    inputPort.setFont(font);
    inputPort.setText("Enter Port: ");
    inputPort.setSize(50);
    inputPort.setPosition(pPortPosition + std::make_pair(promptPort.getSize().first,0));
    inputPort.setText({});
}

void GameStateSelectIPAndPort::onKeyEnter() {
    if (!input)
        return;

    if (!ipSelected) {
        if (numberPos != 3 || numberCounts.back() == 0)
            return;
        ipSelected = true;
        server.setIp(inputIp.getText());
    } else {
        server.setPort(std::stoi(inputPort.getText()));
        nextState = TryToConnect;
        input = false;
    }
}

void GameStateSelectIPAndPort::onTextEntered(char c) {
    if (!input)
        return;

    if (!ipSelected) {
        if (std::isdigit(c))
            if (numberCounts[numberPos] < 3) {
                numberCounts[numberPos]++;
                inputIp += c;
            }
        if (c == '.') {
            if (numberCounts[numberPos] == 0)
                return;
            if (numberPos < 3) {
                numberPos++;
                inputIp += c;
            }
        }
    } else {
        if (std::isdigit(c))
            if (inputPort.getString().size() < 5)
                inputPort += c;
    }
}

void GameStateSelectIPAndPort::onBackSpace() {
    if (!input)
        return;

    if (!ipSelected) {
        if (inputIp.getString().empty())
            return;
        if (inputIp.getString().back() != '.') {
            numberCounts[numberPos]--;
            --inputIp;
        }
        else {
            numberPos--;
            --inputIp;
        }
    } else {
        if (!inputPort.getString().empty())
            --inputPort;
    }
}

void GameStateSelectIPAndPort::restart() {
    numberPos = 0;
    numberCounts = {0,0,0,0};
    ipSelected = false;
    input = true;
    inputIp.clear();
    inputPort.clear();
    nextState = SelectIPAndPort;
}

void GameStateSelectIPAndPort::drawAsBackGround() {
    drawState();
}

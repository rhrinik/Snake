#include "ServerStateWaitingForPlayers.h"

ServerState::States ServerStateWaitingForPlayers::runState(ServerState::States previous) {
    if (previous == Start)
        init();
    if (previous == PlayingGame)
        restart();

    update();

    return nextState;
}

ServerState::States ServerStateWaitingForPlayers::updateState() {
    return nextState;
}

void ServerStateWaitingForPlayers::initState() {
    userInput = std::jthread(&ServerStateWaitingForPlayers::processInput,this);
    if (!makeListener()) {
        std::cerr << "Listener creation fail." << std::endl;
        return;
    }
    selector.add(listener);
    listener.setBlocking(false);
    restart();
}

bool ServerStateWaitingForPlayers::makeListener() {
    return listener.listen(port) == sf::Socket::Done;
}

void ServerStateWaitingForPlayers::connectPlayers() {
    clients.emplace_back();
    clients.emplace_back();
    clients.front().waitToConnect(listener,selector);
    clients.back().waitToConnect(listener,selector);
    std::cout << "Waiting for players to join.... (2/2)" << std::endl;
}

void ServerStateWaitingForPlayers::restart() {
    std::cout << "Starting new game...." << std::endl;
    clients.clear();
    clients.emplace_back();
    clients.emplace_back();
    bool connected1 = false;
    bool connected2 = false;
    int playersConnectedBefore{-1};
    while (!connected1 || !connected2) {
        int playersConnected = (connected1 ? 1 : 0) + (connected2 ? 1 : 0);
        if (playersConnectedBefore != playersConnected) {
            playersConnectedBefore = playersConnected;
            std::cout << "Waiting for players to join.... ("<< playersConnected <<"/2)" << std::endl;
        }
        if (!connected1) {
            connected1 = clients.front().waitToConnect(listener, selector);
        }
        else {
            connected1 = clients.front().isNotDisconnected();
        }
        if (!connected2) {
            connected2 = clients.back().waitToConnect(listener, selector);
        }
        else {
            connected2 = clients.back().isNotDisconnected();
        }
        {
            std::lock_guard<std::mutex> lock(userEndAccess);
            if (!userEnd)
                nextState = PlayingGame;
            else {
                nextState = End;
                return;
            }
        }
    }
    std::cout << "Waiting for players to join.... (2/2)" << std::endl;
    clients.front().sendData({DataFromServer::SnakeState::OtherReady});
    clients.back().sendData({DataFromServer::SnakeState::OtherReady});
}

ServerStateWaitingForPlayers::~ServerStateWaitingForPlayers() {
    listener.close();
}

void ServerStateWaitingForPlayers::processInput() {
    std::string s;
    while (true) {
        std::getline(std::cin, s);
        if (s == "stop" || s == "exit")
            break;
    }
    {
        std::lock_guard<std::mutex> lock(userEndAccess);
        userEnd = true;
    }
    listener.close();
}


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
}

void ServerStateWaitingForPlayers::restart() {
    clients.clear();
    clients.emplace_back();
    clients.emplace_back();
    bool connected1 = false;
    bool connected2 = false;
    while (!connected1 || !connected2) {
        if (!connected1)
            connected1 = clients.front().waitToConnect(listener, selector);
        if (!connected2)
            connected2 = clients.back().waitToConnect(listener, selector);
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


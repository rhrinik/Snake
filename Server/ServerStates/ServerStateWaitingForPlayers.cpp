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
    if (!makeListener()) {
        std::cerr << "Listener creation fail." << std::endl;
        return;
    }
    restart();
}

bool ServerStateWaitingForPlayers::makeListener() {
    return listener.listen(53000) == sf::Socket::Done;
}

void ServerStateWaitingForPlayers::connectPlayers() {
    clients.emplace_back();
    clients.back().waitToConnect(listener);
    nextState = PlayingGame;
}

void ServerStateWaitingForPlayers::restart() {
    clients.clear();
    connectPlayers();
}

ServerStateWaitingForPlayers::~ServerStateWaitingForPlayers() {
    listener.close();
}


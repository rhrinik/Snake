#pragma once
#include "ServerState.h"
#include <thread>
#include <vector>
#include <SFML/Network.hpp>
#include "../Client.h"

class ServerStateWaitingForPlayers : public ServerState {
    States runState(States previous) override;
    States updateState() override;
    void initState() override;
    std::vector<std::jthread> clientReceiveThreads;
    sf::TcpListener listener;
    bool makeListener();
    void connectPlayers();
};

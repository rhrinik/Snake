#pragma once
#include "ServerState.h"
#include <thread>
#include <vector>
#include <iostream>
#include <SFML/Network.hpp>
#include "../Client.h"

class ServerStateWaitingForPlayers : public ServerState {
    std::vector<std::jthread>& clientReceiveThreads;
    std::vector<Client>& clients;
    States runState(States previous) override;
    States updateState() override;
    void initState() override;
    sf::TcpListener listener;
    bool makeListener();
    void connectPlayers();
    void restart();
public:
    ServerStateWaitingForPlayers(std::vector<std::jthread> &clientReceiveThreads, std::vector<Client> &clients)
            : clientReceiveThreads(clientReceiveThreads), clients(clients) {}
};

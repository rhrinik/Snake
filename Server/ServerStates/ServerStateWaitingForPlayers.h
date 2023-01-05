#pragma once
#include "ServerState.h"
#include <thread>
#include <vector>
#include <iostream>
#include <SFML/Network.hpp>
#include "../Client.h"

class ServerStateWaitingForPlayers : public ServerState {
    std::vector<Client>& clients;
    States runState(States previous) override;
    States updateState() override;
    void initState() override;
    sf::TcpListener listener;
    sf::SocketSelector selector;
    int port;
    bool userEnd{false};
    std::mutex userEndAccess;
    bool makeListener();
    void connectPlayers();
    void restart();
    std::jthread userInput;
    void processInput();
public:
    ~ServerStateWaitingForPlayers() override;
    ServerStateWaitingForPlayers(std::vector<Client> &clients, int port)
            : clients(clients),port(port) {}
};

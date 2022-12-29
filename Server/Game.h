#pragma once
#include <cstdlib>
#include <thread>
#include <memory>
#include <SFML/Network.hpp>
#include <iostream>

class Game {
    bool running{false};
    sf::TcpListener listener;
    std::vector<std::jthread> sendThreads;
    std::vector<std::jthread> receiveThreads;
    bool makeListener();
    bool connectPlayers();
    void receivePlayerInput(std::unique_ptr<sf::TcpSocket> client);
public:
    Game() = default;
    bool init();
    void run();
    void update();
    void sendPlayerInfo();
    void getPlayerInput();
    [[nodiscard]] bool isRunning() const;
};

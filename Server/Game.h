#pragma once
#include <cstdlib>
#include <thread>
#include <memory>
#include <SFML/Network.hpp>
#include <iostream>
#include "Client.h"
#include "../Shared/GameObjects/Snake.h"
#include "../Shared/GameObjects/Food.h"
#include "../Shared/Utility/Stopwatch.h"

class Game {
    bool running{false};
    sf::TcpListener listener;
    std::vector<std::jthread> clientReceiveThreads;
    std::vector<Client> clients;
    bool makeListener();
    void connectPlayers();
    void receivePlayerInput(Client& client);
    SnakeBase snake{{160,160}};
    FoodBase food{{320,160}};
    std::binary_semaphore accessToSnake{1};
    Stopwatch stopwatchGameSpeed;
public:
    Game() = default;
    bool init();
    void run();
    void update();
    void sendPlayerInfo();
    void getPlayerInput();
    [[nodiscard]] bool isRunning() const;
};

#pragma once
#include <cstdlib>
#include <thread>
#include <memory>
#include <SFML/Network.hpp>
#include <iostream>
#include "Client.h"
#include "GameObjects/Snake.h"
#include "../Shared/GameObjects/Food.h"
#include "../Shared/Utility/Stopwatch.h"

class Game {
    bool running{false};
    bool gameEnd{false};
    sf::TcpListener listener;
    std::vector<std::jthread> clientReceiveThreads;
    std::vector<Client> clients;
    bool makeListener();
    void connectPlayers();
    void receivePlayerInput(Client& client);
    Snake snake{{160,160}};
    FoodBase food{{320,160}};
    Stopwatch stopwatchGameSpeed;
public:
    Game() = default;
    bool init();
    void run();
    void update();
    void sendPlayerInfo();
    [[nodiscard]] bool isRunning() const;

    bool checkCollisions();

    void sendMoveSnakes();

    bool foodEaten();
};

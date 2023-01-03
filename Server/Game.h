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
#include "../Server/ServerStates/ServerState.h"
#include "../Server/ServerStates/ServerStatePlayingGame.h"
#include "../Server/ServerStates/ServerStatePlayingGame.h"

class Game {
    std::vector<std::unique_ptr<ServerState>> states;
    ServerState::States currentState{ServerState::WaitingForPlayers};
    ServerState::States previousState{ServerState::Start};

    bool running{false};
    bool gameEnd{false};
    sf::TcpListener listener; //ok
    std::vector<std::jthread> clientReceiveThreads; //ok
    std::vector<Client> clients; //ostava tu
    bool makeListener(); //ok
    void connectPlayers(); //ok
    void receivePlayerInput(Client& client); //ok
    Snake snake{{160,160}}; //ok
    FoodBase food{{320,160}}; //ok
    Stopwatch stopwatchGameSpeed; //ok
public:
    Game() = default;
    bool init();
    void run();
    void update();
    void sendPlayerInfo(); //ok
    [[nodiscard]] bool isRunning() const;
    bool checkCollisions(); //ok
    void sendMoveSnakes(); //ok
    bool foodEaten(); //ok
};

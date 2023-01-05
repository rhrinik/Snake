#pragma once
#include <cstdlib>
#include <thread>
#include <mutex>
#include <memory>
#include <SFML/Network.hpp>
#include <iostream>
#include "Client.h"
#include "GameObjects/Snake.h"
#include "../Shared/GameObjects/Food.h"
#include "../Shared/Utility/Stopwatch.h"
#include "../Server/ServerStates/ServerState.h"
#include "../Server/ServerStates/ServerStatePlayingGame.h"
#include "../Server/ServerStates/ServerStateWaitingForPlayers.h"

class Game {
    std::vector<std::unique_ptr<ServerState>> states;
    ServerState::States currentState{ServerState::WaitingForPlayers};
    ServerState::States previousState{ServerState::Start};
    std::vector<Client> clients;
public:
    Game() = default;
    void init(int port);
    void run();
};

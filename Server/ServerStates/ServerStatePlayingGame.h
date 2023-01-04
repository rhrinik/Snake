#pragma once
#include "ServerState.h"
#include "../GameObjects/Snake.h"
#include "../../Shared/GameObjects/Food.h"
#include "../../Shared/Utility/Stopwatch.h"
#include "../Client.h"
#include <thread>

class ServerStatePlayingGame : public ServerState {
    std::vector<Client>& clients;
    States runState(States previous) override;
    States updateState() override;
    void initState() override;
    Snake snake{{160,160}};
    FoodBase food{{320,160}};
    Stopwatch stopwatchGameSpeed;
    void receivePlayerInput(DataFromClient const& data);
    bool checkCollisions();
    void sendMoveSnakes();
    void sendCrash(Client& client);
    bool foodEaten();
    void sendPlayerInfo();
public:
    ServerStatePlayingGame(std::vector<Client> &clients)
            : clients(clients) {}
};

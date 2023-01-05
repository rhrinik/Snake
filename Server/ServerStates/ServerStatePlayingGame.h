#pragma once
#include "ServerState.h"
#include "../GameObjects/Snake.h"
#include "../../Shared/GameObjects/Food.h"
#include "../../Shared/Utility/Stopwatch.h"
#include "../Client.h"
#include "../GameObjects/GameSpace.h"
#include <thread>

class ServerStatePlayingGame : public ServerState {
    std::vector<Client>& clients;
    States runState(States previous) override;
    States updateState() override;
    void initState() override;
    GameSpace gameSpace{{50,37}};
    Stopwatch stopwatchGameSpeed;
    void receivePlayerInput(DataFromClient const& data, Client& client);
    void sendMoveSnakes();
    void sendCrash(Client& client, GameSpace::Player player);
    void sendPutSnake(Client &client, GameSpace::Player player);
    void sendPutFood(Client &client, GameSpace::Player player);
    void sendPlayerInfo();
public:
    ServerStatePlayingGame(std::vector<Client> &clients)
            : clients(clients) {}
};

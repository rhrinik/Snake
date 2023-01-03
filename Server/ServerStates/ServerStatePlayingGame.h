#pragma once
#include "ServerState.h"
#include "../GameObjects/Snake.h"
#include "../../Shared/GameObjects/Food.h"
#include "../../Shared/Utility/Stopwatch.h"
#include "../Client.h"

class ServerStatePlayingGame : public ServerState {
    States runState(States previous) override;
    States updateState() override;
    void initState() override;
    Snake snake{{160,160}};
    FoodBase food{{320,160}};
    Stopwatch stopwatchGameSpeed;
    void receivePlayerInput(Client& client);
    bool checkCollisions();
    void sendMoveSnakes();
    bool foodEaten();
    void sendPlayerInfo();
};

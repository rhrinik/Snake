#pragma once
#include "GameState.h"
#include "../../Shared/Utility/Stopwatch.h"
#include "../GameObjects/Snake.h"
#include "../GameObjects/Food.h"
#include "../Server.h"
#include <SFML/Network.hpp>
#include <iostream>
#include "../../Shared/DataFromServer.h"

class GameStatePlaying : public GameState {
    [[nodiscard]] States runState(States previous) override;
    States updateState() override;
    void drawState() override;
    void initState() override;
    void restart();
    Stopwatch stopwatch;
    Server& server;
    Snake snake{{4,4}, {100, 225, 50}};
    Food food{{8,4},{100, 225, 50}};
    Snake snake2{{4,4}, {65,105,225}};
    Food food2{{8,4},{65,105,225}};
    Snake::Direction finalDirection{Snake::Direction::Right};
public:
    GameStatePlaying(Window &wnd, Graphics &gfx, Server& server) : GameState(wnd, gfx), server(server) {}

    void onKeyUp() override;
    void onKeyDown() override;
    void onKeyLeft() override;
    void onKeyRight() override;
    void onKeyEnter() override;
};

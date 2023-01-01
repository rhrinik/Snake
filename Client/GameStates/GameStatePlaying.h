#pragma once
#include "GameState.h"
#include "../Utility/Stopwatch.h"
#include "../GameObjects/Snake.h"
#include "../GameObjects/Food.h"
#include "../Server.h"
#include <SFML/Network.hpp>
#include <iostream>
#include "../DataToServer.h"

class GameStatePlaying : public GameState {
    [[nodiscard]] States runState(States previous) override;
    void updateState() override;
    void drawState() override;
    void initState() override;
    Stopwatch stopwatchGameSpeed;
    Stopwatch stopwatch;
    Server server;
    Snake snake{{160,160}};
    Food food{{320,160}};
public:
    GameStatePlaying(Window &wnd, Graphics &gfx) : GameState(wnd, gfx) {}

    void onKeyUp() override;
    void onKeyDown() override;
    void onKeyLeft() override;
    void onKeyRight() override;
    void onKeyEnter() override;
};

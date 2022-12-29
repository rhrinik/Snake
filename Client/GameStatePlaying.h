#pragma once
#include "GameState.h"
#include "Stopwatch.h"
#include "Snake.h"
#include <SFML/Network.hpp>
#include <iostream>

class GameStatePlaying : public GameState {
    [[nodiscard]] States runState(Graphics &gfx) override;
    void updateState() override;
    void drawState(Graphics &gfx) override;
    void initState() override;
    Stopwatch stopwatch;
    sf::TcpSocket server;
    Snake snake{{0,0}};
};

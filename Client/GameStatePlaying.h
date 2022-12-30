#pragma once
#include "GameState.h"
#include "Stopwatch.h"
#include "Snake.h"
#include "Food.h"
#include <SFML/Network.hpp>
#include <iostream>

class GameStatePlaying : public GameState {
    [[nodiscard]] States runState(States previous) override;
    void updateState() override;
    void drawState() override;
    void initState() override;
    Stopwatch stopwatchGameSpeed;
    Stopwatch stopwatch;
    sf::TcpSocket server;
    Snake snake{{160,160}};
    Food food{{320,160}};
public:
    GameStatePlaying(Window &wnd, Graphics &gfx) : GameState(wnd, gfx) {}
};

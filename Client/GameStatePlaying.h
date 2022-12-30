#pragma once
#include "GameState.h"
#include "Stopwatch.h"
#include "Snake.h"
#include "Food.h"
#include <SFML/Network.hpp>
#include <iostream>

class GameStatePlaying : public GameState {
    [[nodiscard]] States runState(Window &wnd, Graphics &gfx) override;
    void updateState(Window &wnd) override;
    void drawState(Graphics &gfx) override;
    void initState() override;
    Stopwatch stopwatchGameSpeed;
    Stopwatch stopwatch;
    sf::TcpSocket server;
    Snake snake{{160,160}};
    Food food{{320,160}};
};

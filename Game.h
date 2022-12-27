#pragma once
#include "Graphics.h"
#include "Stopwatch.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <optional>

class Game {
    Graphics& gfx;
public:
    explicit Game(Graphics &gfx) : gfx(gfx) {}
    void run();
    void update();
    void draw();
    bool init();

    bool running{false};
    [[nodiscard]] bool isRunning() const;

    sf::TcpSocket server;
    Stopwatch stopwatch;
};

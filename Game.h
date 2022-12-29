#pragma once

#include "Graphics.h"
#include "Stopwatch.h"
#include "Food.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <optional>

class Game {
    Graphics &gfx;
    Snake snake1 = Snake(SnakePart(std::make_pair(400, 300)), std::make_tuple(0, 255, 0));
    Food food1 = Food(std::make_pair(100, 100));;
public:
    explicit Game(Graphics &gfx) : gfx(gfx) {}

    void run();

    void update();

    void draw();

    bool init();

    bool running{false};


    void foodCollision(Snake &snake, Food &food);

    void gameOver(Snake &snake);

    [[nodiscard]] bool isRunning() const;

    sf::TcpSocket server;
    Stopwatch stopwatch;

};

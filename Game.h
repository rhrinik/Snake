#pragma once

#include "Graphics.h"
#include "Stopwatch.h"
#include "Snake.h"
#include "Food.h"
#include "Constants.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <optional>

class Game {
    Graphics &gfx;
    Snake snake1 = Snake(SnakePart(std::make_pair(SNAKE_STARTING_POS_X, SNAKE_STARTING_POS_Y)));
    Food food1 = Food(std::make_pair(FOOD_STARTING_POS_X, FOOD_STARTING_POS_Y));
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

    void updateDirection(Snake &snake);
};

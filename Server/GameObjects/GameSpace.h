#pragma once
#include "../../Shared/GameObjects/GameSpaceBase.h"
#include "../GameObjects/Snake.h"
#include <mutex>
#include <iostream>

class GameSpace : public GameSpaceBase {
public:
    Snake snake{{4,4}};
    FoodBase food{{8,4}};
    std::mutex tileAccess;
    inline static std::mt19937 rng{std::random_device{}()};
public:
    GameSpace(const std::pair<int, int> &space) : GameSpaceBase(space) {}
    void resetFood(std::pair<int,int> pos) {
        std::lock_guard<std::mutex> lock(tileAccess);
        setEmpty(food.getCoords());
        setNonEmpty(pos);
        food.setPosition(pos);
    }
    [[nodiscard]] std::pair<int,int> getSnakeHead() {
        return snake.getSegments()[0];
    }
    void moveSnake() {
        std::lock_guard<std::mutex> lock(tileAccess);
        GameSpaceBase::moveSnake(snake);
    }
    void resetSnake(std::pair<int,int> pos) {
        std::lock_guard<std::mutex> lock(tileAccess);
        GameSpaceBase::resetSnake(snake, pos);
    }
    void growSnake() {
        GameSpaceBase::growSnake(snake);
    }
    void repositionFood() {
        std::lock_guard<std::mutex> lock(tileAccess);
        setEmpty(food.getCoords());
        std::uniform_int_distribution<int> dist(0, static_cast<int>(emptyTiles.size())-1);
        std::pair<int,int> newCoords = getCoordsFromIndex(dist(rng));
        setNonEmpty(food.getCoords());
        food.setPosition(newCoords);
    }
    [[nodiscard]] std::pair<int, int> getFoodCoords() const {
        return food.getCoords();
    }
    bool foodEaten() {
        return food.getCoords() == snake.getSegments()[0];
    }
    void setSnakeDirection(Snake::Direction dir) {
        snake.setDirection(dir);
    }
    bool checkCollisions() {
        return snake.wallCollision({0, 0}, {tiles.size()/rows, rows}) || snake.selfCollision();
    }
};

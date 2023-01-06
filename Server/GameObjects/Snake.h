#pragma once
#include <vector>
#include <ranges>
#include <algorithm>
#include "../../Shared/Utility/Utilities.h"
#include "../../Shared/GameObjects/Snake.h"
#include <semaphore>

class Snake : public SnakeBase {
    std::binary_semaphore accessToSnake{1};
public:
    explicit Snake(std::pair<int,int> startingPoint) : SnakeBase(startingPoint) {}

    void move() override {
        accessToSnake.acquire();
        SnakeBase::move();
        accessToSnake.release();
    }

    [[nodiscard]] Direction getDirection() {
        accessToSnake.acquire();
        auto ret = SnakeBase::getDirection();
        accessToSnake.release();
        return ret;
    }

    void grow() override {
        accessToSnake.acquire();
        SnakeBase::grow();
        accessToSnake.release();
    }

    void setDirection(Direction newDirection) override {
        accessToSnake.acquire();
        SnakeBase::setDirection(newDirection);
        accessToSnake.release();
    }

    [[nodiscard]] std::vector<std::pair<int, int>> const&getSegments() {
        accessToSnake.acquire();
        auto& ret = SnakeBase::getSegments();
        accessToSnake.release();
        return ret;
    }

    [[nodiscard]] bool selfCollision() {
        accessToSnake.acquire();
        auto ret = SnakeBase::selfCollision();
        accessToSnake.release();
        return ret;
    }

    [[nodiscard]] std::size_t getSize() {
        accessToSnake.acquire();
        auto ret = segments.size();
        accessToSnake.release();
        return ret;
    }

    [[nodiscard]] bool wallCollision(std::pair<int, int> wallTopLeft, std::pair<int, int> wallBotRight) {
        accessToSnake.acquire();
        auto ret = SnakeBase::wallCollision(wallTopLeft, wallBotRight);
        accessToSnake.release();
        return ret;
    }

    void reset(std::pair<int, int> startingPoint) override {
        accessToSnake.acquire();
        SnakeBase::reset(startingPoint);
        accessToSnake.release();
    }
};
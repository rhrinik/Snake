

#ifndef HADIK_SNAKE_H
#define HADIK_SNAKE_H


#include <utility>
#include <tuple>
#include <iostream>
#include <deque>
#include "SnakePart.h"
#include "Food.h"


enum class Directions {
    LEFT, RIGHT, UP, DOWN
};

class Snake {
private:
    std::deque<SnakePart> snakeParts;
    Directions direction = Directions::RIGHT;
public:
    [[nodiscard]] const std::tuple<int, int, int> &getRgb() const;

    [[nodiscard]] SnakePart &getSnakeHead() const {
        return const_cast<SnakePart &>(snakeParts.back());
    }

    [[nodiscard]] Directions getDirection() const {
        return direction;
    }

    void setDirection(Directions newDirection) {
        this->direction = newDirection;
    }

    [[nodiscard]] inline const std::deque<SnakePart> &getSnakeParts() const { return snakeParts; }

    explicit Snake(SnakePart startPart);


    void popTail() { snakeParts.pop_front(); }

    bool selfCollision();

    bool obstacleCollision();

    SnakePart updatePosition();

};


#endif //HADIK_SNAKE_H

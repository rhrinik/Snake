

#ifndef HADIK_SNAKE_H
#define HADIK_SNAKE_H


#include <utility>
#include <tuple>
#include <iostream>
#include <deque>
#include "SnakePart.h"


enum class Directions {LEFT,RIGHT,UP,DOWN};

class Snake {
private:
    std::deque<SnakePart> snakeParts;
    Directions direction = Directions::RIGHT;
public:
    [[nodiscard]] SnakePart& getSnakeHead() const {
        return const_cast<SnakePart &>(snakeParts.back());
    }

public:
    [[nodiscard]] Directions getDirection() const {
        return direction;
    }

    void setDirection(Directions newDirection) {
        this->direction = newDirection;
    }

public:

    const float PART_SIZE = 20;
    const std::tuple<int,int,int> RGB;

    [[nodiscard]] const std::deque<SnakePart> &getSnakeParts() const {return snakeParts;}

public:
    explicit Snake(SnakePart startPart, std::tuple<int,int,int> RGB);
    void addPart(SnakePart part);
    void popTail() {snakeParts.pop_front();}
    bool selfCollision();

};


#endif //HADIK_SNAKE_H


#include "Snake.h"
#include "Food.h"
#include "Constants.h"

Snake::Snake(SnakePart startPart)  {
    snakeParts.emplace_back(startPart);
}

bool Snake::selfCollision() {
    constexpr std::size_t MIN_SIZE_SELF_COLLISION = 4;
    constexpr std::size_t Last_ELEMENT_POSITION_BEFORE_HEAD = 2;

    std::size_t size = snakeParts.size();
    if (size > MIN_SIZE_SELF_COLLISION) {
        for (unsigned int start{}; start < size - Last_ELEMENT_POSITION_BEFORE_HEAD; ++start) {
            if (snakeParts[start].getCoord() == snakeParts.back().getCoord()) return true;
        }
    }
    return false;
}



bool Snake::obstacleCollision() {
    float xHead, yHead;
    std::tie(xHead, yHead) = snakeParts.back().getCoord();
    if (xHead < 0 || yHead < 0 || xHead >= WINDOW_SIZE_WIDTH || yHead >= WINDOW_SIZE_HEIGHT) return true;
    return false;
}

SnakePart Snake::updatePosition() {
    float x, y;
    std::pair<float, float> coords;
    std::tie(x, y) = snakeParts.back().getCoord();
    if (this->direction == Directions::UP) coords = std::make_pair(x, y - SNAKE_PART_SIZE);
    if (this->direction == Directions::DOWN) coords = std::make_pair(x, y + SNAKE_PART_SIZE);
    if (this->direction == Directions::LEFT) coords = std::make_pair(x - SNAKE_PART_SIZE, y);
    if (this->direction == Directions::RIGHT)coords = std::make_pair(x + SNAKE_PART_SIZE, y);
    snakeParts.emplace_back(SnakePart(coords));
}


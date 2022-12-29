

#include "Snake.h"
#include "Food.h"

Snake::Snake(SnakePart startPart, std::tuple<int, int, int> RGB) : RGB{std::move(RGB)} {
    snakeParts.emplace_back(startPart);
}

bool Snake::selfCollision() {
    std::size_t size = snakeParts.size();
    if (size > 4) {
        for (unsigned int start = 0; start < size - 2; ++start) {
            if (snakeParts[start].getCoord() == snakeParts.back().getCoord()) return true;
        }
    }
    return false;
}

void Snake::addPart(SnakePart part) {
    snakeParts.emplace_back(part);
}

bool Snake::obstacleCollision() {
    float xHead, yHead;
    std::tie(xHead, yHead) = snakeParts.back().getCoord();
    if (xHead < 0 || yHead < 0 || xHead > 800 || yHead > 600) return true;
    return false;
}

SnakePart Snake::updatedPosition() {
    float x, y;
    std::pair<float, float> coords;
    std::tie(x, y) = snakeParts.back().getCoord();
    if (this->direction == Directions::UP) coords = std::make_pair(x, y - PART_SIZE);
    if (this->direction == Directions::DOWN) coords = std::make_pair(x, y + PART_SIZE);
    if (this->direction == Directions::LEFT) coords = std::make_pair(x - PART_SIZE, y);
    if (this->direction == Directions::RIGHT)coords = std::make_pair(x + PART_SIZE, y);
    snakeParts.emplace_back(SnakePart(coords));
}


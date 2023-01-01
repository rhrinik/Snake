#pragma once
#include <vector>
#include <ranges>
#include <algorithm>
#include <map>
#include "../../Shared/Utility/Utilities.h"

class SnakeBase {
public:
    enum Direction { Up, Down, Left, Right };
protected:
    static int constexpr snakeSize = 40;
    Direction direction{Right};
    std::vector<std::pair<int,int>> segments;
    inline static std::map<Direction,std::pair<int,int>> const directionMoves = {{Up,{0,-1}},{Down,{0,1}},{Left,{-1,0}},{Right,{1,0}}};
public:
    virtual ~SnakeBase() = default;
    explicit SnakeBase(std::pair<int,int> startingPoint) {
        segments.emplace_back(startingPoint);
    }
    virtual void move() {
        for (std::size_t i = segments.size() - 1; i > 0; --i)
            segments[i] = segments[i-1];
        segments[0] += directionMoves.at(direction) * snakeSize;
    }
    //test
    [[nodiscard]] Direction getDirection() const {
        return direction;
    }
    virtual void grow() {
        segments.emplace_back(segments.back());
    }
    virtual void setDirection(Direction newDirection) {
        if (segments.size() > 2 &&
            directionMoves.at(direction) + directionMoves.at(newDirection) == std::make_pair(0,0))
                return;
        direction = newDirection;
    }
    [[nodiscard]] std::vector<std::pair<int, int>> const& getSegments() const {
        return segments;
    }
    [[nodiscard]] bool selfCollision() const {
        return segments.size() > 4 &&
            std::ranges::any_of(segments | std::views::drop(3),[&](auto const& s){return s == segments[0];});
    }
    [[nodiscard]] bool wallCollision(std::pair<int,int> wallTopLeft, std::pair<int,int> wallBotRight) const {
        return segments[0].first + snakeSize > wallBotRight.first || segments[0].first < wallTopLeft.first ||
                segments[0].second + snakeSize > wallBotRight.second || segments[0].second < wallTopLeft.second;
    }
};
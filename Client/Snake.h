#pragma once
#include <vector>
#include "Graphics.h"
#include <algorithm>
#include "Utilities.h"

class Snake {
public:
    enum Direction { Up, Down, Left, Right };
private:
    Direction direction{Right};
    std::vector<std::pair<int,int>> segments;
    inline static std::map<Direction,std::pair<int,int>> directionMoves = {{Up,{0,-1}},{Down,{0,1}},{Left,{-1,0}},{Right,{1,0}}};
public:
    explicit Snake(std::pair<int,int> startingPoint) {
        segments.emplace_back(startingPoint);
    }
    void draw(Graphics &gfx) const {
        std::ranges::for_each(std::as_const(segments),[&](auto const& p){
            gfx.drawRectangle({p},{p + std::make_pair(40,40)}, Color(100, 250, 50));
            //gfx.drawCircle(p,20,Color(100, 250, 50));
        });
    }
    void move() {
        for (std::size_t i = segments.size() - 1; i > 0; --i)
            segments[i] = segments[i-1];
        segments[0] += directionMoves[direction] * 40;
    }
    void grow() {
        segments.emplace_back(segments.back());
    }
    void setDirection(Direction newDirection) {
        direction = newDirection;
    }
    [[nodiscard]] std::vector<std::pair<int, int>> const& getSegments() const {
        return segments;
    }
};
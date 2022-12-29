#pragma once
#include <vector>
#include "Graphics.h"
#include <algorithm>

inline std::pair<int, int> operator*(std::pair<int, int> p, int x) {
    return {p.first * x, p.second * x};
}

inline std::pair<int, int> operator+(std::pair<int, int> p, std::pair<int, int> p2) {
    return {p.first + p2.first, p.second + p2.second};
}

class Snake {
    std::vector<std::pair<int,int>> segments;
public:
    enum Direction { Up, Down, Left, Right } direction{Right};
    std::pair<int,int> getDirection(Direction d) {
        switch (d) {
            case Up:
                return {0,-1};
            case Down:
                return {0,1};
            case Left:
                return {-1,0};
            case Right:
                return {1,0};
        }
        return {0,0};
    }
    explicit Snake(std::pair<int,int> startingPoint) {
        segments.emplace_back(startingPoint);
    }
    void draw(Graphics &gfx) const {
        std::ranges::for_each(std::as_const(segments),[&](auto const& p){gfx.drawCircle(p,20,Color(100, 250, 50));});
    }
    void move() {
        std::ranges::for_each(segments,[&](auto &p){p = getDirection(direction) * 40 + p;});
    }

};

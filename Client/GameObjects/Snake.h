#pragma once
#include <vector>
#include <ranges>
#include "../Display/Graphics.h"
#include <algorithm>
#include <iostream>
#include <random>
#include "../../Shared/Utility/Utilities.h"
#include "../../Shared/GameObjects/Snake.h"

class Snake : public SnakeBase {
private:
    std::vector<Color> segmentColors;
    Color  snakeColor;
    static int constexpr snakeSize = 40;
    inline static std::mt19937 rng{std::random_device{}()};
    inline static std::uniform_int_distribution<int> distR{-30,30};
    inline static std::uniform_int_distribution<int> distG{-30,30};
    inline static std::uniform_int_distribution<int> distB{-30,30};
public:
    explicit Snake(std::pair<int,int> startingPoint,Color color) : SnakeBase(startingPoint),snakeColor{color} {}
    void draw(Graphics &gfx) const {
        gfx.drawRectangle(segments[0] * snakeSize,segments[0] * snakeSize + std::make_pair(snakeSize,snakeSize), snakeColor);
        for (int i = 1;i < segments.size(); ++i){
            auto const& p = segments[i];
            gfx.drawRectangle(p * snakeSize + 2, p * snakeSize + 2 + std::make_pair((snakeSize-4),(snakeSize-4)), segmentColors[i-1]);
        };
    }
    void grow() override {
        SnakeBase::grow();
        segmentColors.emplace_back(snakeColor + Color(distR(rng),distG(rng),distB(rng)));
    }
};
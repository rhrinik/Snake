#pragma once
#include <vector>
#include <ranges>
#include "../Display/Graphics.h"
#include <algorithm>
#include "../../Shared/Utility/Utilities.h"
#include "../../Shared/GameObjects/Snake.h"

class Snake : public SnakeBase {
private:
    static Color constexpr snakeColor = {100, 250, 50};
    static int constexpr snakeSize = 40;
public:
    explicit Snake(std::pair<int,int> startingPoint) : SnakeBase(startingPoint) {}
    void draw(Graphics &gfx) const {
        std::ranges::for_each(std::as_const(segments),[&](auto const& p){
            gfx.drawRectangle({p * snakeSize},{p * snakeSize + std::make_pair(snakeSize,snakeSize)}, snakeColor);
        });
    }
};
#pragma once
#include <utility>
#include <random>
#include "../Display/Graphics.h"
#include "../../Shared/Utility/Utilities.h"
#include "../../Shared/GameObjects/Food.h"

class Food : public FoodBase {
    static Color constexpr foodColor = {255, 0, 0};
    static int constexpr foodSize = 40;
public:
    explicit Food(std::pair<int, int> coords) : FoodBase(std::move(coords)) {}
    void draw(Graphics& gfx) {
        gfx.drawCircle(coords * foodSize, foodSize/2, foodColor);
    }
};
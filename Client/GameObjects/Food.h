#pragma once
#include <utility>
#include <random>
#include "../Display/Graphics.h"
#include "../../Shared/Utility/Utilities.h"
#include "../../Shared/GameObjects/Food.h"

class Food : public FoodBase {
     Color  foodColor;
    static int constexpr foodSize = 40;
public:
    explicit Food(std::pair<int, int> coords,Color color) : FoodBase(std::move(coords)),foodColor{color} {}
    void draw(Graphics& gfx) {
        gfx.drawCircle(coords * foodSize, foodSize/2, foodColor);
    }
};
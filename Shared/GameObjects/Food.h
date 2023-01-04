#pragma once
#include <utility>
#include <random>
#include "../../Shared/Utility/Utilities.h"

class FoodBase {
protected:
    std::pair<int,int> coords;
    inline static std::mt19937 rng{std::random_device{}()};
public:
    explicit FoodBase(std::pair<int, int> coords) : coords(std::move(coords)) {}
    /*void reposition(std::pair<int,int> topLeft, std::pair<int,int> botRight) {
        std::uniform_int_distribution<int> xRng(topLeft.first, botRight.first);
        std::uniform_int_distribution<int> yRng(topLeft.second, botRight.second);
        coords = {xRng(rng), yRng(rng)};
    }*/
    void setPosition(std::pair<int,int> newCoords) {
        coords = newCoords;
    }
    [[nodiscard]] std::pair<int, int> getCoords() const {
        return coords;
    }
};
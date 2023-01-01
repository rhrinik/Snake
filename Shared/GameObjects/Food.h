#pragma once
#include <utility>
#include <random>
#include "../../Shared/Utility/Utilities.h"

class FoodBase {
protected:
    static int constexpr foodSize = 40;
    std::pair<int,int> coords;
    inline static std::mt19937 rng{std::random_device{}()};
public:
    explicit FoodBase(std::pair<int, int> coords) : coords(std::move(coords)) {}
    void reposition(std::pair<int,int> validSpace) {
        std::uniform_int_distribution<int> xRng(0, validSpace.first / foodSize);
        std::uniform_int_distribution<int> yRng(0, validSpace.second / foodSize);
        coords = {xRng(rng) * foodSize, yRng(rng) * foodSize};
    }
    [[nodiscard]] std::pair<int, int> getCoords() const {
        return coords;
    }
};
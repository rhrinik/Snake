#pragma once
#include <utility>
#include <random>
#include "Graphics.h"
#include "Utilities.h"

class Food {
    std::pair<int,int> coords;
    inline static std::mt19937 rng{std::random_device{}()};
public:
    explicit Food(std::pair<int, int> coords) : coords(std::move(coords)) {}
    void draw(Graphics& gfx) {
        gfx.drawCircle(coords, 20, Color(255,0,0));
    }
    void reposition(std::pair<int,int> validSpace) {
        std::uniform_int_distribution<int> xRng(0, validSpace.first / 40);
        std::uniform_int_distribution<int> yRng(0, validSpace.second / 40);
        coords = {xRng(rng) * 40, yRng(rng) * 40};
    }
    [[nodiscard]] std::pair<int, int> getCoords() const {
        return coords;
    }
};
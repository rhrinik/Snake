
#ifndef HADIK_FOOD_H
#define HADIK_FOOD_H


#include <utility>
#include <tuple>
#include <random>
#include "Constants.h"
#include <chrono>

class Food {

public:
    explicit Food(std::pair<float, float> coord) : coord(std::move(coord)) {}

    [[nodiscard]] inline const std::pair<float, float> &getCoord() const {return coord;}

    void generateFood();

private:
    std::pair<float, float> coord;
    inline static std::mt19937 random{static_cast<std::mt19937::result_type>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    inline static std::uniform_int_distribution randCoordX{0,static_cast<int>((WINDOW_SIZE_WIDTH-SNAKE_PART_SIZE)/SNAKE_PART_SIZE)} ;
    inline static std::uniform_int_distribution randCoordY{0,static_cast<int>((WINDOW_SIZE_HEIGHT-SNAKE_PART_SIZE)/SNAKE_PART_SIZE)} ;

};





#endif //HADIK_FOOD_H

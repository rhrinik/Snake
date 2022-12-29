
#ifndef HADIK_FOOD_H
#define HADIK_FOOD_H


#include <utility>
#include <tuple>

class Food {

public:
    explicit Food(std::pair<float, float> coord) : coord(std::move(coord)) {}

public:
    [[nodiscard]] inline const std::pair<float, float> &getCoord() const {return coord;}

    void generateFood();

private:
    std::pair<float, float> coord;
};



#endif //HADIK_FOOD_H

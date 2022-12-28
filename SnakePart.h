

#ifndef HADIK_SNAKEPART_H
#define HADIK_SNAKEPART_H


#include <utility>

class SnakePart {
public:
    explicit SnakePart(std::pair<float, float> coord) : coord(std::move(coord)) {}

    [[nodiscard]] const std::pair<float, float> &getCoord() const { return coord; }

    void setCoord(const std::pair<float, float> position) { SnakePart::coord = position; }




private:
    std::pair<float, float> coord;
};




#endif //HADIK_SNAKEPART_H

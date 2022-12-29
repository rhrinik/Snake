
#include "Food.h"
#include "Constants.h"
#include <random>

void Food::generateFood() {
    //TODO: For Debugging, make better generator
    float x = SNAKE_PART_SIZE + SNAKE_PART_SIZE * (rand() % (int)((WINDOW_SIZE_WIDTH-SNAKE_PART_SIZE)/SNAKE_PART_SIZE));
    float y = SNAKE_PART_SIZE + SNAKE_PART_SIZE * (rand() % (int)((WINDOW_SIZE_HEIGHT-SNAKE_PART_SIZE)/SNAKE_PART_SIZE));

    this->coord = std::make_pair(x, y);
}


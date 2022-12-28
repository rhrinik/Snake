
#include "Food.h"
#include <random>
void Food::generateFood() {
    float x = 20 + 20* (rand() % 36);
    float y = 20 + 20* (rand() % 28);

    this->coord = std::make_pair(x,y);
}


#include <iostream>
#include "Food.h"




void Food::generateFood() {

    float x =randCoordX(random) * SNAKE_PART_SIZE;
    float y = randCoordY(random) * SNAKE_PART_SIZE;
    this->coord = {x,y};





}




#include "Snake.h"

Snake::Snake(SnakePart startPart, std::tuple<int, int, int> RGB) : RGB{std::move(RGB)} {
    snakeParts.emplace_back(startPart);
}

bool Snake::selfCollision() {
    std::size_t size = snakeParts.size();
    if( size> 4){
        for(unsigned int start = 0 ;start < size-2  ;++start){
            if(snakeParts[start].getCoord() == snakeParts.back().getCoord()) return true;
        }
    }
    return false;
}

void Snake::addPart(SnakePart part) {
    snakeParts.emplace_back(part);
}

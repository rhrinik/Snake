#pragma once
#include "Food.h"
#include "Snake.h"

class GameSpaceBase {
protected:
    enum TileState : char { Empty, NonEmpty };
    std::vector<TileState> tiles;
    int rows;
    std::vector<int> emptyTiles;
    [[nodiscard]] int getIndexFromCoords(std::pair<int,int> at) const {
        return at.first * rows + at.second;
    }
    [[nodiscard]] std::pair<int,int> getCoordsFromIndex(int index) const {
        return {index / rows, index % rows};
    }
    TileState& getTileAt(std::pair<int,int> at) {
        return tiles[getIndexFromCoords(at)];
    }
    [[nodiscard]] bool isValid(std::pair<int,int> at) {
        return getIndexFromCoords(at) >=0 && getIndexFromCoords(at) < tiles.size();
    }
    void setEmpty(std::pair<int,int> at) {
        if (!isValid(at))
            return;
        if (getTileAt(at) == Empty)
            return;
        getTileAt(at) = Empty;
        emptyTiles.emplace_back(getIndexFromCoords(at));
    }
    void setNonEmpty(std::pair<int,int> at) {
        if (!isValid(at))
            return;
        if (getTileAt(at) == NonEmpty)
            return;
        getTileAt(at) = NonEmpty;
        remove_at(emptyTiles,getIndexFromCoords(at));
    }
public:
    GameSpaceBase(std::pair<int,int> space)
    : tiles(space.first * space.second, Empty), rows(space.second), emptyTiles(space.first * space.second) {
        std::iota(emptyTiles.begin(),emptyTiles.end(),0);
    }
    void moveSnake(SnakeBase& snake) {
        setEmpty(snake.getSegments().back());
        snake.move();
        setNonEmpty(snake.getSegments().back());
        setNonEmpty(snake.getSegments()[0]);
    }
    void resetSnake(SnakeBase& snake, std::pair<int,int> pos) {
        for (auto const& seg : snake.getSegments())
            setEmpty(seg);
        snake.reset(pos);
        setNonEmpty(pos);
    }
    void growSnake(SnakeBase& snake) {
        snake.grow();
    }
};

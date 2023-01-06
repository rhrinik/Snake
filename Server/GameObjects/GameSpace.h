#pragma once
#include "../../Shared/GameObjects/GameSpaceBase.h"
#include "../GameObjects/Snake.h"
#include <mutex>
#include <iostream>

class GameSpace : public GameSpaceBase {
public:
    enum Player {Player1, Player2, Both, None};
private:
    Snake snake{{4,4}};
    Snake snake2{{4,4}};
    FoodBase food{{8,4}};
    FoodBase food2{{8,4}};
    std::mutex tileAccess;
    std::map<Player, Snake&> snakesMap = {{Player1, snake}, {Player2, snake2}};
    std::map<Player, FoodBase&> foodMap = {{Player1, food}, {Player2, food2}};
    std::map<Player, Snake::Direction> startMap = {{Player1, Snake::Right}, {Player2, Snake::Left}};
    inline static std::mt19937 rng{std::random_device{}()};
public:
    GameSpace(const std::pair<int, int> &space) : GameSpaceBase(space) {}
    Player otherPlayer(Player player) {
        return player == Player1 ? Player2 : Player1;
    }
    void resetFood(std::pair<int,int> pos, Player player) {
        std::lock_guard<std::mutex> lock(tileAccess);
        setEmpty(foodMap.at(player).getCoords());
        setNonEmpty(pos);
        foodMap.at(player).setPosition(pos);
    }
    [[nodiscard]] std::pair<int,int> getSnakeHead(Player player) {
        return snakesMap.at(player).getSegments()[0];
    }
    void moveSnake(Player player) {
        std::lock_guard<std::mutex> lock(tileAccess);
        GameSpaceBase::moveSnake(snakesMap.at(player));
    }
    void resetSnake(std::pair<int,int> pos,Player player) {
        std::lock_guard<std::mutex> lock(tileAccess);
        GameSpaceBase::resetSnake(snakesMap.at(player), pos);
        snakesMap.at(player).setDirection(startMap[player]);
    }
    void growSnake(Player player) {
        GameSpaceBase::growSnake(snakesMap.at(player));
    }
    void repositionFood(Player player) {
        std::lock_guard<std::mutex> lock(tileAccess);
        setEmpty(foodMap.at(player).getCoords());
        std::uniform_int_distribution<int> dist(0, static_cast<int>(emptyTiles.size())-1);
        std::pair<int,int> newCoords = getCoordsFromIndex(dist(rng));
        setNonEmpty(foodMap.at(player).getCoords());
        foodMap.at(player).setPosition(newCoords);
    }
    [[nodiscard]] std::pair<int, int> getFoodCoords(Player player) const {
        return foodMap.at(player).getCoords();
    }
    bool foodEaten(Player player) {
        return foodMap.at(player).getCoords() == snakesMap.at(player).getSegments()[0];
    }
    void setSnakeDirection(Snake::Direction dir, Player player) {
        snakesMap.at(player).setDirection(dir);
    }
    Snake::Direction getSnakeDirection (Player player) {
        return snakesMap.at(player).getDirection();
    }
    bool checkCollisions(Player player) {
        return snakesMap.at(player).wallCollision({0, 0}, {tiles.size()/rows, rows}) || snakesMap.at(player).selfCollision();
    }
    Player checkSnakeCollisions() {
        bool snake1crash = std::ranges::any_of(snake.getSegments(), [&](auto const &s) { return s == snake2.getSegments()[0];});
        bool snake2crash = std::ranges::any_of(snake2.getSegments(), [&](auto const &s) { return s == snake.getSegments()[0];});

        if (snake1crash && snake2crash) {
            if (snake.getSize() == snake2.getSize())
                return Both;
            if (snake.getSize() > snake2.getSize()) {
                return Player1;
            }
            return Player2;
        }
        if (snake1crash)
            return Player1;
        if (snake2crash)
            return Player2;
        return None;
    }
};

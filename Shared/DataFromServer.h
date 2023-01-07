#pragma once
#include <cstdint>
#include <SFML/Network.hpp>
#include <utility>
#include "GameObjects/Snake.h"

class DataFromServer {
    std::pair<std::int32_t,std::int32_t> newFoodCoordsThisSnake{0, 0};
    std::pair<std::int32_t,std::int32_t> newFoodCoordsOtherSnake{0, 0};
    std::int32_t snakeState{};
    std::int32_t otherSnakeDirection{};
public:
    enum SnakeState { Move, EatAndMove, Crash, Win, OtherEat, BothEat, Draw, PutSnakes, PutFood, OtherReady };
    DataFromServer() = default;
    DataFromServer(SnakeState snakeState, SnakeBase::Direction direction, std::pair<int,int> newFoodCoords, std::pair<int,int> newFoodOther)
        : snakeState(static_cast<std::int32_t>(snakeState)),
          otherSnakeDirection(static_cast<std::int32_t>(direction)),
          newFoodCoordsThisSnake(std::move(newFoodCoords)),
          newFoodCoordsOtherSnake(std::move(newFoodOther)) {}
    DataFromServer(SnakeState snakeState,SnakeBase::Direction direction) : DataFromServer(snakeState,direction,{0,0},{0,0}) {}
    DataFromServer(SnakeState snakeState,SnakeBase::Direction direction,std::pair<int,int> newFoodCoords)
        : DataFromServer(snakeState,direction,{0,0},{0,0}) {
        switch (snakeState) {
            case EatAndMove:
                newFoodCoordsThisSnake = newFoodCoords;
                break;
            case OtherEat:
                newFoodCoordsOtherSnake = newFoodCoords;
                break;
            default:
                break;
        }
    }
    DataFromServer(SnakeState snakeState) : DataFromServer(snakeState, SnakeBase::Direction::Right) {}
    [[nodiscard]] SnakeState getSnakeState() const {
        return static_cast<SnakeState>(snakeState);
    }
    [[nodiscard]] std::pair<std::int32_t, std::int32_t> const& getNewFoodCoords() const {
        return newFoodCoordsThisSnake;
    }
    [[nodiscard]] std::pair<std::int32_t, std::int32_t> const& getOtherFoodCoords() const {
        return newFoodCoordsOtherSnake;
    }
    [[nodiscard]] SnakeBase::Direction getOtherDirection() const {
        return static_cast<SnakeBase::Direction>(otherSnakeDirection);
    }
    [[nodiscard]] sf::Packet toPacket() const {
        sf::Packet packet;
        packet << snakeState <<
            newFoodCoordsThisSnake.first <<
            newFoodCoordsThisSnake.second <<
            newFoodCoordsOtherSnake.first <<
            newFoodCoordsOtherSnake.second <<
            otherSnakeDirection;
        return packet;
    }
    static DataFromServer fromPacket(sf::Packet packet) {
        DataFromServer data{};
        packet >> data.snakeState >>
               data.newFoodCoordsThisSnake.first >>
               data.newFoodCoordsThisSnake.second >>
               data.newFoodCoordsOtherSnake.first >>
               data.newFoodCoordsOtherSnake.second >>
               data.otherSnakeDirection;
        return data;
    }
};

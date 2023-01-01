#pragma once
#include <cstdint>
#include <SFML/Network.hpp>
#include <utility>
#include "GameObjects/Snake.h"

class DataFromServer {
    std::int32_t direction{};
    std::pair<std::int32_t,std::int32_t> newFoodCoords{0,0};
    std::int32_t snakeState{};
public:
    enum SnakeState { Move, EatAndMove, Crash, Win };
    DataFromServer() = default;
    DataFromServer(SnakeState snakeState, SnakeBase::Direction direction, std::pair<int,int> newFoodCoords = {0,0})
        : snakeState(static_cast<std::int32_t>(snakeState)),
          direction(static_cast<std::int32_t>(direction)),
          newFoodCoords(std::move(newFoodCoords)) {}
    [[nodiscard]] SnakeBase::Direction getDirection() const {
        return static_cast<SnakeBase::Direction>(direction);
    }
    [[nodiscard]] SnakeState getSnakeState() const {
        return static_cast<SnakeState>(snakeState);
    }
    [[nodiscard]] std::pair<std::int32_t, std::int32_t> const& getNewFoodCoords() const {
        return newFoodCoords;
    }
    [[nodiscard]] sf::Packet toPacket() const {
        sf::Packet packet;
        packet << snakeState << direction << newFoodCoords.first << newFoodCoords.second;
        return packet;
    }
    static DataFromServer fromPacket(sf::Packet packet) {
        DataFromServer data{};
        packet >> data.snakeState >> data.direction >> data.newFoodCoords.first >> data.newFoodCoords.second;
        return data;
    }
};

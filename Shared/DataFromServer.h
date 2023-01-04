#pragma once
#include <cstdint>
#include <SFML/Network.hpp>
#include <utility>
#include "GameObjects/Snake.h"

class DataFromServer {
    std::pair<std::int32_t,std::int32_t> newFoodCoords{0,0};
    std::int32_t snakeState{};
public:
    enum SnakeState { Move, EatAndMove, Crash, Win };
    DataFromServer() = default;
    DataFromServer(SnakeState snakeState, std::pair<int,int> newFoodCoords = {0,0})
        : snakeState(static_cast<std::int32_t>(snakeState)),
          newFoodCoords(std::move(newFoodCoords)) {}
    [[nodiscard]] SnakeState getSnakeState() const {
        return static_cast<SnakeState>(snakeState);
    }
    [[nodiscard]] std::pair<std::int32_t, std::int32_t> const& getNewFoodCoords() const {
        return newFoodCoords;
    }
    [[nodiscard]] sf::Packet toPacket() const {
        sf::Packet packet;
        packet << snakeState << newFoodCoords.first << newFoodCoords.second;
        return packet;
    }
    static DataFromServer fromPacket(sf::Packet packet) {
        DataFromServer data{};
        packet >> data.snakeState >> data.newFoodCoords.first >> data.newFoodCoords.second;
        return data;
    }
};

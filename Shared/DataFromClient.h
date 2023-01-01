#pragma once
#include <cstdint>
#include <SFML/Network.hpp>
#include "GameObjects/Snake.h"

class DataFromClient {
    std::int32_t direction;
public:
    DataFromClient() = default;
    DataFromClient(SnakeBase::Direction direction)
        : direction(static_cast<std::int32_t>(direction)) {}
    [[nodiscard]] SnakeBase::Direction getDirection() const {
        return static_cast<SnakeBase::Direction>(direction);
    }
    [[nodiscard]] sf::Packet toPacket() const {
        sf::Packet packet;
        packet << direction;
        return packet;
    }
    static DataFromClient fromPacket(sf::Packet packet) {
        DataFromClient data{};
        packet >> data.direction;
        return data;
    }
};
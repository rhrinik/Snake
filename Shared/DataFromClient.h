#pragma once
#include <cstdint>
#include <SFML/Network.hpp>
#include "GameObjects/Snake.h"

class DataFromClient {
    std::int32_t direction;
    std::int32_t ok;
public:
    DataFromClient() = default;
    DataFromClient(SnakeBase::Direction direction, bool ok = false)
        : direction(static_cast<std::int32_t>(direction)),
        ok(ok ? 1 : 0) {}
    [[nodiscard]] SnakeBase::Direction getDirection() const {
        return static_cast<SnakeBase::Direction>(direction);
    }
    [[nodiscard]] bool getOk() const {
        return static_cast<bool>(ok);
    }
    [[nodiscard]] sf::Packet toPacket() const {
        sf::Packet packet;
        packet << direction << ok;
        return packet;
    }
    static DataFromClient fromPacket(sf::Packet packet) {
        DataFromClient data{};
        packet >> data.direction >> data.ok;
        return data;
    }
};
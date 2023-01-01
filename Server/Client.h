#pragma once
#include <SFML/Network.hpp>
#include <memory>
#include <utility>
#include "../Shared/DataFromServer.h"
#include "../Shared/DataFromClient.h"
#include "GameObjects/Snake.h"

class Client {
    std::shared_ptr<sf::TcpSocket> socket;
public:
    Client() : socket(std::make_shared<sf::TcpSocket>()) {}
    /*Client(Client const& c) = default;
    Client(Client && c) noexcept = default;
    Client& operator=(Client c) {
        this->socket = std::move(c.socket);
        return *this;
    }
    ~Client() = default;*/
    bool waitToConnect(sf::TcpListener& listener) {
        sf::Socket::Status status = listener.accept(*socket);
        return status == sf::Socket::Done;
    }
    void sendData(DataFromServer data) {
        std::int32_t x;
        sf::Packet packet;
        packet << static_cast<std::int32_t>(data.direction);
        socket->send(packet);
    }
    DataFromClient receiveData() {
        std::int32_t x;
        sf::Packet packet;
        //if (client->receive(packet) == sf::Socket::Status::Disconnected) break;
        socket->receive(packet);
        packet >> x;
        return {static_cast<Snake::Direction>(x)};
    }
};

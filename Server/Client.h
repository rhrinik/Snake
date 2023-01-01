#pragma once
#include <SFML/Network.hpp>
#include <memory>
#include <utility>
#include "../Shared/DataFromServer.h"
#include "../Shared/DataFromClient.h"
#include "../Shared/GameObjects/Snake.h"

class Client {
    std::shared_ptr<sf::TcpSocket> socket;
public:
    Client() : socket(std::make_shared<sf::TcpSocket>()) {}
    bool waitToConnect(sf::TcpListener& listener) {
        sf::Socket::Status status = listener.accept(*socket);
        return status == sf::Socket::Done;
    }
    void sendData(DataFromServer data) {
        sf::Packet packet = data.toPacket();
        socket->send(packet);
    }
    DataFromClient receiveData() {
        sf::Packet packet;
        socket->receive(packet);
        return DataFromClient::fromPacket(packet);
    }
};

//if (client->receive(packet) == sf::Socket::Status::Disconnected) break;
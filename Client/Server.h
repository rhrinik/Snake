#pragma once
#include <SFML/Network.hpp>
#include "../Shared/DataFromClient.h"
#include "../Shared/DataFromServer.h"

class Server {
    sf::TcpSocket socket;
public:
    bool connect() {
        sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
        return status == sf::Socket::Done;
    }
    void sendData(DataFromClient data) {
        std::int32_t x;
        sf::Packet packet;
        packet << static_cast<std::int32_t>(data.direction);
        socket.send(packet);
    }
    DataFromServer receiveData() {
        std::int32_t x;
        sf::Packet packet;
        socket.receive(packet);
        packet >> x;
        return {x};
    }
};

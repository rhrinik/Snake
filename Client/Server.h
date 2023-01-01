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
        sf::Packet packet = data.toPacket();
        socket.send(packet);
    }
    DataFromServer receiveData() {
        sf::Packet packet;
        socket.receive(packet);
        return DataFromServer::fromPacket(packet);
    }
};

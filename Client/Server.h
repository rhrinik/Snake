#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include "../Shared/DataFromClient.h"
#include "../Shared/DataFromServer.h"

class Server {
    sf::TcpSocket socket;
public:
    ~Server() {
        disconnect();
    }
    void disconnect() {
        socket.disconnect();
    }
    bool connect() {
        sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
        return status == sf::Socket::Done;
    }
    void sendData(DataFromClient data) {
        sf::Packet packet = data.toPacket();
        sf::TcpSocket::Status status = socket.send(packet);
    }
    DataFromServer receiveData() {
        sf::Packet packet;
        sf::TcpSocket::Status status = socket.receive(packet);
        return DataFromServer::fromPacket(packet);
    }
};

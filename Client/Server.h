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
        std::cout << data.getOk() << std::endl;
        sf::TcpSocket::Status status = socket.send(packet);
        switch (status) {
            case sf::Socket::Done:
                std::cout << "Done" << std::endl;
                break;
            case sf::Socket::NotReady:
                std::cout << "NotReady" << std::endl;
                break;
            case sf::Socket::Partial:
                std::cout << "Partial" << std::endl;
                break;
            case sf::Socket::Disconnected:
                std::cout << "Disconnected" << std::endl;
                break;
            case sf::Socket::Error:
                std::cout << "Error" << std::endl;
                break;
        }
    }
    DataFromServer receiveData() {
        sf::Packet packet;
        sf::TcpSocket::Status status = socket.receive(packet);
        if (status != sf::TcpSocket::Status::Done) {
            std::cout << "kek cleint not done ";
            if (status == sf::TcpSocket::Status::Disconnected)
                std::cout << "kek cleint disc " << std::endl;
            else
                std::cout << "kek cleint else " << std::endl;
        }
        return DataFromServer::fromPacket(packet);
    }
};

#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include "../Shared/DataFromClient.h"
#include "../Shared/DataFromServer.h"

class Server {
    sf::TcpSocket socket;
public:
    ~Server() {
        std::cout << "~Server() Disconnected" << std::endl;
        disconnect();
    }
    void disconnect() {
        std::cout << "disconnect() Disconnected" << std::endl;
        socket.disconnect();
    }
    bool connect() {
        sf::Socket::Status status = socket.connect("127.0.0.1", 53000, sf::seconds(2));
        return status == sf::Socket::Done;
    }
    void sendData(DataFromClient data) {
        sf::Packet packet = data.toPacket();
        sf::TcpSocket::Status status = socket.send(packet);
    }
    DataFromServer receiveData() {
        sf::Packet packet;
        sf::TcpSocket::Status status = socket.receive(packet);
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
        return DataFromServer::fromPacket(packet);
    }
    void sendOk() {
        sendData({SnakeBase::Direction::Right, true});
    }
    void okAndDisconnect() {
        sendOk();
        disconnect();
    }
};

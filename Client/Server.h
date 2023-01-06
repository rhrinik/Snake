#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <utility>
#include "../Shared/DataFromClient.h"
#include "../Shared/DataFromServer.h"

class Server {
    sf::TcpSocket socket;
    std::string ip;
    int port;
public:
    void setPort(int newPort) {
        port = newPort;
    }
    void setIp(std::string newIp) {
        ip = std::move(newIp);
    }
    ~Server() {
        std::cout << "~Server() Disconnected" << std::endl;
        disconnect();
    }
    void disconnect() {
        std::cout << "disconnect() Disconnected" << std::endl;
        socket.disconnect();
    }
    bool connect() {
        //sf::Socket::Status status = socket.connect(ip, port, sf::seconds(2));
        sf::Socket::Status status = socket.connect("127.0.0.1", 53000, sf::seconds(2));
        switch (status) {
            case sf::Socket::Done:
                std::cout << "connect Done" << std::endl;
                break;
            case sf::Socket::NotReady:
                std::cout << "connect NotReady" << std::endl;
                break;
            case sf::Socket::Partial:
                std::cout << "connect Partial" << std::endl;
                break;
            case sf::Socket::Disconnected:
                std::cout << "connect Disconnected" << std::endl;
                break;
            case sf::Socket::Error:
                std::cout << "connect Error" << std::endl;
                break;
        }
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

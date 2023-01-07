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
    bool connected{false};
public:
    [[nodiscard]] bool isConnected() const {
        return connected;
    }
    void setConnected(bool isConnected) {
        Server::connected = isConnected;
    }
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
        //sf::Socket::Status status = socket.connect(ip, port, sf::seconds(0.01));
        sf::Socket::Status status = socket.connect("127.0.0.1", 53000, sf::seconds(0.01));
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
                connected = false;
                std::cout << "connect Disconnected" << std::endl;
                break;
            case sf::Socket::Error:
                std::cout << "connect Error" << std::endl;
                break;
        }
        return status == sf::Socket::Done || status == sf::Socket::NotReady;
    }
    void sendData(DataFromClient data) {
        sf::Packet packet = data.toPacket();
        sf::TcpSocket::Status status = socket.send(packet);
    }
    std::pair<sf::TcpSocket::Status,DataFromServer> receiveData() {
        socket.setBlocking(false);
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
                connected = false;
                std::cout << "Disconnected" << std::endl;
                break;
            case sf::Socket::Error:
                std::cout << "Error" << std::endl;
                break;
        }
        return {status,DataFromServer::fromPacket(packet)};
    }
    void sendOk() {
        sendData({SnakeBase::Direction::Right, true});
    }
    void okAndDisconnect() {
        sendOk();
        disconnect();
    }
};

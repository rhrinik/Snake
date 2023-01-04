#pragma once
#include <SFML/Network.hpp>
#include <memory>
#include <utility>
#include <thread>
#include <iostream>
#include <functional>
#include "../Shared/DataFromServer.h"
#include "../Shared/DataFromClient.h"
#include "../Shared/GameObjects/Snake.h"

class Client {
    std::shared_ptr<sf::TcpSocket> socket;
    std::unique_ptr<std::jthread> thread;
    bool continueReceivingData;
public:
    ~Client() {
        socket->disconnect();
    }
    Client() : socket(std::make_shared<sf::TcpSocket>()) {}
    Client(Client &&client) noexcept : socket(client.socket), thread(std::move(client.thread)) {}
    bool waitToConnect(sf::TcpListener& listener) {
        sf::Socket::Status status = listener.accept(*socket);
        return status == sf::Socket::Done;
    }
    void sendData(DataFromServer data) {
        sf::Packet packet = data.toPacket();
        sf::TcpSocket::Status status = socket->send(packet);
    }
    void startReceivingData(std::function<void(DataFromClient const&)> f) {
        continueReceivingData = true;
        thread = std::make_unique<std::jthread>(&Client::receiveData, this, f);
    }
    std::pair<sf::TcpSocket::Status, bool> receiveWithTimeout(const std::shared_ptr<sf::TcpSocket>& sock, sf::Packet& packet, int timeout) {
        sf::SocketSelector socketSelector;
        socketSelector.add(*sock);
        if (socketSelector.wait(sf::seconds(5))) {
            return {sock->receive(packet),true};
        }
        return {sf::TcpSocket::Status::Disconnected, false};
    }
    void receiveData(std::function<void(DataFromClient const&)> const& f) {
        while (continueReceivingData) {
            sf::Packet packet;
            auto status = receiveWithTimeout(socket, packet, 2);
            if (!status.second) {
                socket->disconnect();
                return;
            }
            if (status.first == sf::TcpSocket::Status::Disconnected)
                return;
            DataFromClient dataFromClient = DataFromClient::fromPacket(packet);
            if (dataFromClient.getOk()) {
                socket->disconnect();
                return;
            }
            f(DataFromClient::fromPacket(packet));
        }
    }
    void waitForOk() {
        thread->join();
    }
};

//if (client->receive(packet) == sf::Socket::Status::Disconnected) break;
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
#include "GameObjects/GameSpace.h"

class Client {
    std::shared_ptr<sf::TcpSocket> socket;
    std::unique_ptr<std::jthread> thread;
    bool continueReceivingData;
    GameSpace::Player player{GameSpace::Player1};
    bool sendDataThisTime{false};
    //std::mutex startStop;
public:
    void dataSent() {
        sendDataThisTime = true;
    }
    void canSendMore() {
        sendDataThisTime = false;
    };
    [[nodiscard]] bool alreadySent() const {
        return sendDataThisTime;
    }
    bool isNotDisconnected() {
        std::size_t size;
        bool blocks = socket->isBlocking();
        socket->setBlocking(false);
        auto status = socket->receive(&size, 0, size) != sf::Socket::Disconnected;
        socket->setBlocking(blocks);
        return status;
    }
    ~Client() {
        socket->disconnect();
    }
    Client() : socket(std::make_shared<sf::TcpSocket>()) {}
    Client(Client &&client) noexcept : socket(client.socket), thread(std::move(client.thread)) {}
    bool waitToConnect(sf::TcpListener& listener, sf::SocketSelector& selector) {
        /*selector.wait(sf::seconds(0.5));
        if (!selector.isReady(listener))
            return false;*/
        sf::Socket::Status status = listener.accept(*socket);
        return status == sf::Socket::Done;
    }
    void setPlayer(GameSpace::Player newPlayer) {
        player = newPlayer;
    }
    [[nodiscard]] GameSpace::Player getPlayer() const {
        return player;
    }
    void sendData(DataFromServer data) {
        sf::Packet packet = data.toPacket();
        sf::TcpSocket::Status status = socket->send(packet);
    }
    void startReceivingData(std::function<void(DataFromClient const&, Client& client)> f) {
        continueReceivingData = true;
        thread = std::make_unique<std::jthread>(&Client::receiveData, this, f);
    }
    std::pair<sf::TcpSocket::Status, bool> receiveWithTimeout(const std::shared_ptr<sf::TcpSocket>& sock, sf::Packet& packet, int timeout) {
        sf::SocketSelector socketSelector;
        socketSelector.add(*sock);
        if (socketSelector.wait(sf::seconds(timeout))) {
            return {sock->receive(packet),true};
        }
        return {sf::TcpSocket::Status::Disconnected, false};
    }
    void stopReceivingData() {
        //std::lock_guard<std::mutex> lock(startStop);
        //continueReceivingData = false;
    }
    void receiveData(std::function<void(DataFromClient const&,Client& client)> const& f) {
        //std::lock_guard<std::mutex> lock(startStop);
        while (continueReceivingData) {
            sf::Packet packet;
            //auto status = receiveWithTimeout(socket, packet, 10);
            auto status = socket->receive(packet);
            /*if (!status.second) {
                socket->disconnect();
                return;
            }*/
            //if (status.first == sf::TcpSocket::Status::Disconnected)
            if (status == sf::TcpSocket::Status::Disconnected)
                return;
            DataFromClient dataFromClient = DataFromClient::fromPacket(packet);
            if (dataFromClient.getOk()) {
                socket->disconnect();
                return;
            }
            f(DataFromClient::fromPacket(packet), *this);
        }
    }
    void waitForOk() {
        thread->join();
    }
};

//if (client->receive(packet) == sf::Socket::Status::Disconnected) break;
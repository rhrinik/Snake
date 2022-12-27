#include "Game.h"

void Game::run() {
    getPlayerInput();
    update();
    sendPlayerInfo();
}

void Game::update() {
}

void Game::sendPlayerInfo() {
}

void Game::getPlayerInput() {
}

bool Game::isRunning() const {
    return running;
}

bool Game::makeListener() {
    return listener.listen(53000) == sf::Socket::Done;
}

bool Game::connectPlayers() {
    for (int i = 0; i < 2; ++i) {
        auto client = std::make_unique<sf::TcpSocket>();
        if (listener.accept(*client) != sf::Socket::Done)
            return false;
        receiveThreads.emplace_back(std::jthread(&Game::receivePlayerInput, this, std::move(client)));
    }
    return true;
}

void Game::receivePlayerInput(std::unique_ptr<sf::TcpSocket> client) {
    while (true) {
        std::int32_t x;
        std::string s;

        sf::Packet packet;
        if (client->receive(packet) == sf::Socket::Status::Disconnected) break;
        packet >> s >> x;
        std::cout << s << x << std::endl;
    }
}

bool Game::init() {
    if (!makeListener()) {
        std::cerr << "Listener creation fail." << std::endl;
        return false;
    }

    if (!connectPlayers()) {
        std::cerr << "Error connecting players." << std::endl;
        return false;
    }

    return running = true;
}

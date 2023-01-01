#include "Game.h"

void Game::run() {
    getPlayerInput();
    update();
    sendPlayerInfo();
}

void Game::update() {
    if (stopwatchGameSpeed.removeTime(0.1)) {
        accessToSnake.acquire();
        snake.move();
        accessToSnake.release();

        if (food.getCoords() == snake.getSegments()[0]) {
            snake.grow();
            food.reposition({2000,1500});
            clients.back().sendData({DataFromServer::EatAndMove, snake.getDirection(), food.getCoords()});
            return;
        }

        clients.back().sendData({DataFromServer::Move, snake.getDirection()});
    }
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

void Game::connectPlayers() {
    clients.emplace_back();
    clients.back().waitToConnect(listener);
    clientReceiveThreads.emplace_back(std::jthread(&Game::receivePlayerInput, this, std::ref(clients.back())));
}

void Game::receivePlayerInput(Client& client) {
    while (true) {
        DataFromClient data = client.receiveData();
        accessToSnake.acquire();
        snake.setDirection(static_cast<SnakeBase::Direction>(data.getDirection()));
        accessToSnake.release();
    }
}

bool Game::init() {
    if (!makeListener()) {
        std::cerr << "Listener creation fail." << std::endl;
        return false;
    }

    connectPlayers();

    /*if (!connectPlayers()) {
        std::cerr << "Error connecting players." << std::endl;
        return false;
    }*/
    stopwatchGameSpeed.reset();
    return running = true;
}

#include "Game.h"

void Game::run() {
    while (currentState != ServerState::End) {
        auto const prev = previousState;
        previousState = currentState;
        currentState = states[static_cast<int>(currentState)]->run(prev);
    }
    /*if (!stopwatchGameSpeed.removeTime(0.1))
        return;
    update();
    sendPlayerInfo();*/
}

/*void Game::update() {
    if (gameEnd)
        return;

    snake.move();

    if (checkCollisions()) {
        gameEnd = true;
        return;
    }
}*/

/*void Game::sendMoveSnakes() {
    if (foodEaten()) {
        snake.grow();
        food.reposition({2000, 1500});
        clients.back().sendData({DataFromServer::EatAndMove, snake.getDirection(), food.getCoords()});
    } else {
        clients.back().sendData({DataFromServer::Move, snake.getDirection()});
    }
}*/

/*bool Game::foodEaten() {
    return food.getCoords() == snake.getSegments()[0];
}*/

/*bool Game::checkCollisions() {
    if (snake.wallCollision({0, 0}, {2000, 1500}) || snake.selfCollision()) {
        clients.back().sendData({DataFromServer::Crash, snake.getDirection()});
        return true;
    }
    return false;
}*/

/*void Game::sendPlayerInfo() {
    if (gameEnd)
        return;
    sendMoveSnakes();
}*/

/*bool Game::isRunning() const {
    return running;
}*/

/*bool Game::makeListener() {
    return listener.listen(53000) == sf::Socket::Done;
}*/

/*void Game::connectPlayers() {
    clients.emplace_back();
    clients.back().waitToConnect(listener);
    clientReceiveThreads.emplace_back(std::jthread(&Game::receivePlayerInput, this, std::ref(clients.back())));
}*/

/*void Game::receivePlayerInput(Client& client) {
    while (true) {
        DataFromClient data = client.receiveData();
        snake.setDirection(data.getDirection());
    }
}*/

void Game::init() {
    states.emplace_back(std::make_unique<ServerStateWaitingForPlayers>(clientReceiveThreads, clients));
    states.emplace_back(std::make_unique<ServerStatePlayingGame>(clientReceiveThreads, clients));
    /*if (!makeListener()) {
        std::cerr << "Listener creation fail." << std::endl;
        return;
    }*/

    //connectPlayers();

    /*if (!connectPlayers()) {
        std::cerr << "Error connecting players." << std::endl;
        return false;
    }*/
    //stopwatchGameSpeed.reset();
    //running = true;
}

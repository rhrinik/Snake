#include "ServerStatePlayingGame.h"

ServerState::States ServerStatePlayingGame::runState(ServerState::States previous) {
    if (previous != PlayingGame)
        init();

    update();
    return nextState;
}

ServerState::States ServerStatePlayingGame::updateState() {
    if (!stopwatchGameSpeed.removeTime(0.1))
        return PlayingGame;

    snake.move();

    sendPlayerInfo();
    return nextState;
}

void ServerStatePlayingGame::initState() {
    for (auto &client : clients)
        clientReceiveThreads.emplace_back(std::jthread(&ServerStatePlayingGame::receivePlayerInput, this, std::ref(client)));
    snake.reset({160,160});
    stopwatchGameSpeed.reset();
    nextState = PlayingGame;
}

void ServerStatePlayingGame::sendMoveSnakes() {
    if (foodEaten()) {
        snake.grow();
        food.reposition({2000, 1500});
        clients.back().sendData({DataFromServer::EatAndMove, snake.getDirection(), food.getCoords()});
    } else {
        clients.back().sendData({DataFromServer::Move, snake.getDirection()});
    }
}

bool ServerStatePlayingGame::foodEaten() {
    return food.getCoords() == snake.getSegments()[0];
}

void ServerStatePlayingGame::receivePlayerInput(Client &client) {
    while (true) {
        DataFromClient data = client.receiveData();
        snake.setDirection(data.getDirection());
    }
}

bool ServerStatePlayingGame::checkCollisions() {
    return snake.wallCollision({0, 0}, {2000, 1500}) || snake.selfCollision();
}

void ServerStatePlayingGame::sendPlayerInfo() {
    if (checkCollisions()) {
        sendCrash(clients.back());
        nextState = WaitingForPlayers;
    } else
        sendMoveSnakes();
}

void ServerStatePlayingGame::sendCrash(Client &client) {
    client.sendData({DataFromServer::Crash, snake.getDirection()});
}

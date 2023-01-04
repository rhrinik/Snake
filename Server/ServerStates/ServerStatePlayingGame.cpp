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

    gameSpace.moveSnake();

    sendPlayerInfo();
    return nextState;
}

void ServerStatePlayingGame::sendPutSnake(Client &client) {
    client.sendData({DataFromServer::PutSnakes,Snake::Direction::Right,gameSpace.getSnakeHead(),{20,20}}); // temp right, temp other food;
}

void ServerStatePlayingGame::sendPutFood(Client &client) {
    client.sendData({DataFromServer::PutFood,Snake::Direction::Right,gameSpace.getFoodCoords(),{20,20}}); // temp right, temp other food;
}

void ServerStatePlayingGame::initState() {
    gameSpace.resetSnake({20,20});
    gameSpace.resetFood({1,1});
    for (auto &client : clients) {
        sendPutSnake(client);
        sendPutFood(client);
    }
    for (auto &client : clients)
        client.startReceivingData([&](DataFromClient const& data){receivePlayerInput(data);});
    stopwatchGameSpeed.reset();
    nextState = PlayingGame;
}

void ServerStatePlayingGame::sendMoveSnakes() {
    if (gameSpace.foodEaten()) {
        gameSpace.growSnake();
        gameSpace.repositionFood();
        clients.back().sendData({DataFromServer::EatAndMove,Snake::Direction::Right,gameSpace.getFoodCoords()}); // temp right;
    } else {
        clients.back().sendData({DataFromServer::Move,Snake::Direction::Right}); // temp right;
    }
}

void ServerStatePlayingGame::receivePlayerInput(DataFromClient const& data) {
    gameSpace.setSnakeDirection(data.getDirection());
}

void ServerStatePlayingGame::sendPlayerInfo() {
    if (gameSpace.checkCollisions()) {
        sendCrash(clients.back());
        for (auto &client : clients)
            client.waitForOk();
        nextState = WaitingForPlayers;
    } else
        sendMoveSnakes();
}

void ServerStatePlayingGame::sendCrash(Client &client) {
    client.sendData({DataFromServer::Crash,Snake::Direction::Right}); // temp right;
}

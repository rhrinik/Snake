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

void ServerStatePlayingGame::initState() {
    for (auto &client : clients)
        client.startReceivingData([&](DataFromClient const& data){receivePlayerInput(data);});
    gameSpace.resetSnake({4,4});
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

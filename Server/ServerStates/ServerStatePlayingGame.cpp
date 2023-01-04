#include "ServerStatePlayingGame.h"

ServerState::States ServerStatePlayingGame::runState(ServerState::States previous) {
    if (previous != PlayingGame)
        init();

    update();
    return nextState;
}

ServerState::States ServerStatePlayingGame::updateState() {
    if (!stopwatchGameSpeed.removeTime(0.5))
        return PlayingGame;

    gameSpace.moveSnake(GameSpace::Player1);
    gameSpace.moveSnake(GameSpace::Player2);

    sendPlayerInfo();
    return nextState;
}

void ServerStatePlayingGame::sendPutSnake(Client &client, GameSpace::Player player) {
    client.sendData({DataFromServer::PutSnakes,
                     Snake::Direction::Right,
                     gameSpace.getSnakeHead(player),
                     gameSpace.getSnakeHead(gameSpace.otherPlayer(player))});
}

void ServerStatePlayingGame::sendPutFood(Client &client, GameSpace::Player player) {
    client.sendData({DataFromServer::PutFood,
                     Snake::Direction::Right,
                     gameSpace.getFoodCoords(player),
                     gameSpace.getFoodCoords(gameSpace.otherPlayer(player))}); // temp right, temp other food;
}

void ServerStatePlayingGame::initState() {
    gameSpace.resetSnake({3,3}, GameSpace::Player1);
    gameSpace.resetFood({1,1}, GameSpace::Player1);

    gameSpace.resetSnake({20,20}, GameSpace::Player2);
    gameSpace.resetFood({10,10}, GameSpace::Player2);

    sendPutSnake(clients[0],GameSpace::Player1);
    sendPutFood(clients[0],GameSpace::Player1);

    sendPutSnake(clients[1],GameSpace::Player2);
    sendPutFood(clients[1],GameSpace::Player2);

    for (auto &client : clients)
        client.startReceivingData([&](DataFromClient const& data){receivePlayerInput(data);});
    stopwatchGameSpeed.reset();
    nextState = PlayingGame;
}

void ServerStatePlayingGame::sendMoveSnakes() {
    /*if (gameSpace.foodEaten()) {
        gameSpace.growSnake();
        gameSpace.repositionFood();
        clients.back().sendData({DataFromServer::EatAndMove,Snake::Direction::Right,gameSpace.getFoodCoords()}); // temp right;
    } else {
        clients.back().sendData({DataFromServer::Move,Snake::Direction::Right}); // temp right;
    }*/
    if (gameSpace.foodEaten(GameSpace::Player1)) {
        gameSpace.growSnake(GameSpace::Player1);
        gameSpace.repositionFood(GameSpace::Player1);
        clients.back().sendData({DataFromServer::EatAndMove,Snake::Direction::Right,gameSpace.getFoodCoords(GameSpace::Player1)}); // temp right;
    } else {
        clients.back().sendData({DataFromServer::Move,Snake::Direction::Right}); // temp right;
    }
}

void ServerStatePlayingGame::receivePlayerInput(DataFromClient const& data) {
    //gameSpace.setSnakeDirection(data.getDirection());
    gameSpace.setSnakeDirection(data.getDirection(),GameSpace::Player1);
}

void ServerStatePlayingGame::sendPlayerInfo() {
    /*if (gameSpace.checkCollisions()) {
        sendCrash(clients.back());
        for (auto &client : clients)
            client.waitForOk();
        nextState = WaitingForPlayers;
    } else
        sendMoveSnakes();*/
    if (gameSpace.checkCollisions(GameSpace::Player1)) {
        sendCrash(clients.back(),GameSpace::Player1);
        for (auto &client : clients)
            client.waitForOk();
        nextState = WaitingForPlayers;
    } else
        sendMoveSnakes();
}

void ServerStatePlayingGame::sendCrash(Client &client, GameSpace::Player player) {
    client.sendData({DataFromServer::Crash,Snake::Direction::Right}); // temp right;
}

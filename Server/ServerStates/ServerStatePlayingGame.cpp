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

    {
        std::lock_guard<std::mutex> lock(accessToSend);
        putSnakesDone = true;
        readyToReceive.notify_all();
        gameSpace.moveSnake(GameSpace::Player1);
        gameSpace.moveSnake(GameSpace::Player2);

        sendPlayerInfo();
        for (auto &client : clients)
            client.canSendMore();
    }
    if (nextState == WaitingForPlayers)
        for (auto &client : clients)
            client.waitForOk();
    return nextState;
}

void ServerStatePlayingGame::sendPutSnake(Client &client, GameSpace::Player player) {
    client.sendData({DataFromServer::PutSnakes,
                     SnakeBase::Direction::Right,
                     gameSpace.getSnakeHead(player),
                     gameSpace.getSnakeHead(gameSpace.otherPlayer(player))});
}

void ServerStatePlayingGame::sendPutFood(Client &client, GameSpace::Player player) {
    client.sendData({DataFromServer::PutFood,
                     SnakeBase::Direction::Right,
                     gameSpace.getFoodCoords(player),
                     gameSpace.getFoodCoords(gameSpace.otherPlayer(player))});
}

void ServerStatePlayingGame::initState() {
    putSnakesDone = false;
    gameSpace.resetSnake({3,3}, GameSpace::Player1);
    gameSpace.resetFood({1,1}, GameSpace::Player1);

    gameSpace.resetSnake({20,20}, GameSpace::Player2);
    gameSpace.resetFood({10,10}, GameSpace::Player2);

    sendPutSnake(clients[1],GameSpace::Player1);
    sendPutFood(clients[1],GameSpace::Player1);

    sendPutSnake(clients[0],GameSpace::Player2);
    sendPutFood(clients[0],GameSpace::Player2);

    clients.back().setPlayer(GameSpace::Player1);
    clients.front().setPlayer(GameSpace::Player2);
    for (auto &client : clients)
        client.startReceivingData([&](DataFromClient const& data,Client& client){receivePlayerInput(data, client);});
    stopwatchGameSpeed.reset();
    nextState = PlayingGame;
}

void ServerStatePlayingGame::sendMoveSnakes() {
    bool player1eat = gameSpace.foodEaten(GameSpace::Player1);
    bool player2eat = gameSpace.foodEaten(GameSpace::Player2);

    if (player1eat && player2eat) {
        gameSpace.growSnake(GameSpace::Player1);
        gameSpace.growSnake(GameSpace::Player2);
        gameSpace.repositionFood(GameSpace::Player1);
        gameSpace.repositionFood(GameSpace::Player2);
        clients.back().sendData({DataFromServer::BothEat, gameSpace.getSnakeDirection(GameSpace::Player2),
                                 gameSpace.getFoodCoords(GameSpace::Player1),
                                 gameSpace.getFoodCoords(GameSpace::Player2)});
        clients.front().sendData({DataFromServer::BothEat, gameSpace.getSnakeDirection(GameSpace::Player1),
                                  gameSpace.getFoodCoords(GameSpace::Player2),
                                  gameSpace.getFoodCoords(GameSpace::Player1)});
    }

    if (!player1eat && !player2eat) {
        clients.front().sendData({DataFromServer::Move, gameSpace.getSnakeDirection(GameSpace::Player1)});
        clients.back().sendData({DataFromServer::Move, gameSpace.getSnakeDirection(GameSpace::Player2)});
    }

    if (player1eat) {
        gameSpace.growSnake(GameSpace::Player1);
        gameSpace.repositionFood(GameSpace::Player1);
        clients.back().sendData({DataFromServer::EatAndMove, gameSpace.getSnakeDirection(GameSpace::Player2),
                                 gameSpace.getFoodCoords(GameSpace::Player1)});
        clients.front().sendData({DataFromServer::OtherEat, gameSpace.getSnakeDirection(GameSpace::Player1), {0, 0},
                                  gameSpace.getFoodCoords(GameSpace::Player1)});
    }

    if (player2eat) {
        gameSpace.growSnake(GameSpace::Player2);
        gameSpace.repositionFood(GameSpace::Player2);
        clients.front().sendData({DataFromServer::EatAndMove, gameSpace.getSnakeDirection(GameSpace::Player1),
                                  gameSpace.getFoodCoords(GameSpace::Player2)});
        clients.back().sendData({DataFromServer::OtherEat, gameSpace.getSnakeDirection(GameSpace::Player2), {0, 0},
                                 gameSpace.getFoodCoords(GameSpace::Player2)});
    }
}

void ServerStatePlayingGame::receivePlayerInput(DataFromClient const& data, Client& client) {
    std::unique_lock<std::mutex> lock(accessToSend);
    readyToReceive.wait(lock,[&](){return putSnakesDone;});
    if (client.alreadySent())
        return;
    client.dataSent();
    gameSpace.setSnakeDirection(data.getDirection(),client.getPlayer());
}

void ServerStatePlayingGame::sendPlayerInfo() {
    GameSpace::Player crash = gameSpace.checkSnakeCollisions();

    if (crash == GameSpace::Both) {
        sendDraw(clients.back(),GameSpace::Player1);
        sendDraw(clients.front(),GameSpace::Player2);
        endGame();
        return;
    }

    if ((crash == GameSpace::Player1) || gameSpace.checkCollisions(GameSpace::Player1)) {
        sendCrash(clients.back(),GameSpace::Player1);
        sendWin(clients.front(),GameSpace::Player2);
        endGame();
        return;
    }

    if ((crash == GameSpace::Player2) || gameSpace.checkCollisions(GameSpace::Player2)) {
        sendCrash(clients.front(),GameSpace::Player2);
        sendWin(clients.back(),GameSpace::Player1);
        endGame();
        return;
    }
    {

        sendMoveSnakes();
    }
}

void ServerStatePlayingGame::endGame() {
    /*for (auto &client : clients)
        client.stopReceivingData();*/
    nextState = WaitingForPlayers;
}

void ServerStatePlayingGame::sendCrash(Client &client, GameSpace::Player player) {
    client.sendData({DataFromServer::Crash,gameSpace.getSnakeDirection(gameSpace.otherPlayer(player))});
}

void ServerStatePlayingGame::sendWin(Client &client, GameSpace::Player player) {
    client.sendData({DataFromServer::Win,gameSpace.getSnakeDirection(gameSpace.otherPlayer(player))});
}

void ServerStatePlayingGame::sendDraw(Client &client, GameSpace::Player player) {
    client.sendData({DataFromServer::Draw,gameSpace.getSnakeDirection(gameSpace.otherPlayer(player))});
}
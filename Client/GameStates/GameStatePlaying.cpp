#include "GameStatePlaying.h"

GameState::States GameStatePlaying::runState(States previous) {
    if (previous == Menu)
        init();

    auto state = update();
    draw();

    return state;
}

GameState::States GameStatePlaying::updateState() {
    DataFromServer data = server.receiveData();
    switch (data.getSnakeState()) {
        case DataFromServer::BothEat:
            //snake2.grow();
            //food2.setPosition(data.getOtherFoodCoords()); prepare
        case DataFromServer::EatAndMove:
            snake.grow();
            food.setPosition(data.getNewFoodCoords());
        case DataFromServer::Move:
            snake.move();
            //snake2.setDirection(data.getOtherDirection()); prepare;
            //snake2.move(); prepare;
            return Playing;
        case DataFromServer::OtherEat:
            //snake2.grow();
            //food2.setPosition(data.getOtherFoodCoords()); prepare
            //snake.move();
            //snake2.setDirection(data.getOtherDirection()); prepare;
            //snake2.move(); prepare;
            return Playing;

        case DataFromServer::PutSnakes:
            snake.setDirection(data.getOtherDirection());
            snake.reset(data.getNewFoodCoords());
            //snake2.reset(data.getOtherFoodCoords()); prepare
            return Playing;
        case DataFromServer::PutFood:
            food.setPosition(data.getNewFoodCoords());
            // food2.setPosition(data.getOtherFoodCoords()); prepare
            return Playing;

        case DataFromServer::Crash:
            server.okAndDisconnect();
            return Lose;
        case DataFromServer::Win:
            server.okAndDisconnect();
            return Win;
        case DataFromServer::Draw:
            server.okAndDisconnect();
            return Draw;
    }
    return Playing;
}

void GameStatePlaying::drawState() {
    snake.draw(gfx);
    //snake2.draw(gfx); prepare
    food.draw(gfx);
    //food2.draw(gfx); prepare
}

void GameStatePlaying::initState() {
    server.connect();
    restart();
}

void GameStatePlaying::onKeyUp() {
    server.sendData({Snake::Direction::Up});
    snake.setDirection(Snake::Direction::Up);
}

void GameStatePlaying::onKeyDown() {
    server.sendData({Snake::Direction::Down});
    snake.setDirection(Snake::Direction::Down);
}

void GameStatePlaying::onKeyLeft() {
    server.sendData({Snake::Direction::Left});
    snake.setDirection(Snake::Direction::Left);
}

void GameStatePlaying::onKeyRight() {
    server.sendData({Snake::Direction::Right});
    snake.setDirection(Snake::Direction::Right);
}

void GameStatePlaying::onKeyEnter() {
}

void GameStatePlaying::restart() {
    stopwatch.reset();
}

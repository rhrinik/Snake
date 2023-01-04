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
        case DataFromServer::EatAndMove:
            snake.grow();
            food.setPosition(data.getNewFoodCoords());
        case DataFromServer::Move:
            snake.move();
            return Playing;
        case DataFromServer::Crash:
            server.sendData({Snake::Direction::Right, true});
            server.disconnect();
            return Lose;
        case DataFromServer::Win:
            break;
        case DataFromServer::OtherEat:
            break;
        case DataFromServer::BothEat:
            break;
        case DataFromServer::Draw:
            break;
    }
    return Playing;
}

void GameStatePlaying::drawState() {
    snake.draw(gfx);
    food.draw(gfx);
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
    snake.reset({4,4});
}

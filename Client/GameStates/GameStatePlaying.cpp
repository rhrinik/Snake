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
            snake.setDirection(data.getDirection());
            snake.move();
            return Playing;
        case DataFromServer::Crash:
            std::cout << "got crash" << std::endl;
            server.sendData({Snake::Direction::Right, true});
            server.disconnect();
            return Lose;
        case DataFromServer::Win:
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
}

void GameStatePlaying::onKeyDown() {
    server.sendData({Snake::Direction::Down});
}

void GameStatePlaying::onKeyLeft() {
    server.sendData({Snake::Direction::Left});
}

void GameStatePlaying::onKeyRight() {
    server.sendData({Snake::Direction::Right});
}

void GameStatePlaying::onKeyEnter() {
}

void GameStatePlaying::restart() {
    stopwatch.reset();
    snake.reset({160,160});
}

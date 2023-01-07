#include "GameStatePlaying.h"

GameState::States GameStatePlaying::runState(States previous) {
    if (previous == Menu)
        init();
    if (previous == SelectIPAndPort)
        init();

    auto state = update();
    draw();

    return state;
}

GameState::States GameStatePlaying::updateState() {
    server.sendData(finalDirection);
    snake.setDirection(finalDirection);

    auto dataReceived = server.receiveData();
    switch (dataReceived.first) {
        case sf::Socket::Disconnected:
        case sf::Socket::Error:
            nextState = Menu;
            return Menu;
        case sf::Socket::NotReady:
        case sf::Socket::Partial:
            return Playing;
        case sf::Socket::Done:
            break;
    }
    auto &data = dataReceived.second;
    switch (data.getSnakeState()) {
        case DataFromServer::BothEat:
            snake2.grow();
            food2.setPosition(data.getOtherFoodCoords());
        case DataFromServer::EatAndMove:
            snake.grow();
            food.setPosition(data.getNewFoodCoords());
        case DataFromServer::Move:
            snake.move();
            snake2.setDirection(data.getOtherDirection());
            snake2.move();
            return Playing;
        case DataFromServer::OtherEat:
            snake2.grow();
            food2.setPosition(data.getOtherFoodCoords());
            snake.move();
            snake2.setDirection(data.getOtherDirection());
            snake2.move();
            return Playing;

        case DataFromServer::PutSnakes:
            snake.setDirection(data.getOtherDirection());
            snake.reset(data.getNewFoodCoords());
            snake2.reset(data.getOtherFoodCoords());
            return Playing;
        case DataFromServer::PutFood:
            food.setPosition(data.getNewFoodCoords());
            food2.setPosition(data.getOtherFoodCoords());
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
        default:
            break;
    }
    return Playing;
}

void GameStatePlaying::drawState() {
    snake.draw(gfx);
    snake2.draw(gfx);
    food.draw(gfx);
    food2.draw(gfx);
}

void GameStatePlaying::initState() {
    restart();
}

void GameStatePlaying::onKeyUp() {
    finalDirection = Snake::Direction::Up;
}

void GameStatePlaying::onKeyDown() {
    finalDirection = Snake::Direction::Down;
}

void GameStatePlaying::onKeyLeft() {
    finalDirection = Snake::Direction::Left;
}

void GameStatePlaying::onKeyRight() {
    finalDirection = Snake::Direction::Right;
}

void GameStatePlaying::onKeyEnter() {
}

void GameStatePlaying::restart() {
    stopwatch.reset();
}

#include "GameStatePlaying.h"

GameState::States GameStatePlaying::runState(States previous) {
    if (wnd.isWindowClosed())
        return End;
    if (previous != Playing)
        init();

    update();
    draw();

    return Playing;
}

void GameStatePlaying::updateState() {
    DataFromServer data = server.receiveData();
    snake.setDirection(static_cast<Snake::Direction>(data.direction));
    snake.move();

    /*if (stopwatchGameSpeed.removeTime(0.1))
        snake.move();

    if (food.getCoords() == snake.getSegments()[0]) {
        snake.grow();
        food.reposition({2000,1500});
    }
    if (snake.wallCollision({0,0},{2000,1500}) || snake.selfCollision())
        std::cout << "OUCH" << std::endl;*/
}

void GameStatePlaying::drawState() {
    snake.draw(gfx);
    food.draw(gfx);
}

void GameStatePlaying::initState() {
    stopwatchGameSpeed.reset();
    stopwatch.reset();
    wnd.registerObject(*this);
    server.connect();
}

void GameStatePlaying::onKeyUp() {
    server.sendData({Snake::Direction::Up});
    //snake.setDirection(Snake::Direction::Up);
}

void GameStatePlaying::onKeyDown() {
    server.sendData({Snake::Direction::Down});
    //snake.setDirection(Snake::Direction::Down);
}

void GameStatePlaying::onKeyLeft() {
    server.sendData({Snake::Direction::Left});
    //snake.setDirection(Snake::Direction::Left);
}

void GameStatePlaying::onKeyRight() {
    server.sendData({Snake::Direction::Right});
    //snake.setDirection(Snake::Direction::Right);
}

void GameStatePlaying::onKeyEnter() {
}

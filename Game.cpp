#include "Game.h"

void Game::run() {
    gfx.beginFrame();
    update();
    draw();
    gfx.endFrame();
}

void Game::draw() {

    gfx.drawFood(food1);
    gfx.drawSnake(snake1);
}

void Game::update() {
    if (!stopwatch.removeTime(1))
        return;

    gfx.updateDirection(snake1);

    foodCollision(snake1, food1);
    gameOver(snake1);


//
//    std::int32_t x;
//    std::string s = "message: ";
//    sf::Packet packet;
//    packet << s << rand() % 100;
//    server.send(packet);
//    std::cout << "Message sent" << std::endl;


}

bool Game::init() {
    sf::Socket::Status status = server.connect("127.0.0.1", 53000);
    if (status != sf::Socket::Done) {
        std::cerr << "Connection failure." << std::endl;
        return false;
    }
    stopwatch.reset();
    return running = true;
}

bool Game::isRunning() const {
    return running;
}


void Game::foodCollision(Snake &snake, Food &food) {

    snake.getSnakeHead().getCoord() == food.getCoord() ? food.generateFood() : snake.popTail();
}

void Game::gameOver(Snake &snake) {
    if (snake.obstacleCollision() || snake.selfCollision()) {
        std::cout << "OUCH\n";
        gfx.closeWindow();
    }
}


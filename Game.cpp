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

    //TODO: tiddy up
    Directions dir = updateDirection(snake1);
    snake1.setDirection(dir);


    snake1.updatedPosition();

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


Directions Game::updateDirection(const Snake &snake) { //TODO: move to Graphics or Snake or create new Class
    auto dir = snake.getDirection();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && dir != Directions::RIGHT)return Directions::LEFT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && dir != Directions::LEFT)return Directions::RIGHT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && dir != Directions::DOWN)return Directions::UP;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && dir != Directions::UP) return Directions::DOWN;
    return dir;
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


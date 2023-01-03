#include "Game.h"

void Game::run() {
    gfx.beginFrame();
    update();
    draw();
    gfx.endFrame();
}

void Game::draw() {

    gfx.drawFood(food1.getCoord().first,food1.getCoord().second);
    for(auto part: snake1.getSnakeParts()) {
        gfx.drawSnake(part.getCoord().first,part.getCoord().second);
    }
}

void Game::update() {
    if (!stopwatch.removeTime(1))
        return;

    updateDirection(snake1);

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

void Game::updateDirection(Snake &snake) {
    auto dir = snake.getDirection();

    if (gfx.getKP() == 'A' && dir != Directions::RIGHT) dir = Directions::LEFT;
    if (gfx.getKP() == 'D'  && dir != Directions::LEFT) dir = Directions::RIGHT;
    if (gfx.getKP() == 'W'  && dir != Directions::DOWN) dir = Directions::UP;
    if (gfx.getKP() == 'S'  && dir != Directions::UP) dir = Directions::DOWN;
    snake.setDirection(dir);
    snake.updatePosition();
}




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

    Directions dir = updateDirection(snake1);
    snake1.setDirection(dir);
    auto head = snake1.getSnakeHead();
    auto part = updatedPosition( head, dir, snake1.PART_SIZE);



    snake1.addPart(part);

    foodCollision(head, food1)?food1.generateFood():snake1.popTail();

    if(obstacleCollision(snake1.getSnakeHead()) || snake1.selfCollision()) gameOver();


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


Directions Game::updateDirection(const Snake& snake) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && snake.getDirection() != Directions::RIGHT)  return Directions::LEFT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && snake.getDirection() != Directions::LEFT) return Directions::RIGHT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && snake.getDirection() != Directions::DOWN) return Directions::UP;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && snake.getDirection() != Directions::UP)  return Directions::DOWN;
    return snake.getDirection();
}

SnakePart Game::updatedPosition(SnakePart& snakeHead, Directions dir, float partSize){
    float x,y;
    std::pair<float,float> coords;
    std::tie(x,y) = snakeHead.getCoord();
    if(dir == Directions::UP)  coords = std::make_pair(x,y - partSize);
    if(dir == Directions::DOWN) coords = std::make_pair(x,y + partSize);
    if(dir == Directions::LEFT) coords = std::make_pair(x - partSize,y );
    if(dir == Directions::RIGHT)coords = std::make_pair(x +  partSize,y );
    snakeHead = SnakePart(coords);
    return SnakePart(coords);

}



bool Game::foodCollision(SnakePart &snakeHead, Food &food) {
    float xHead,yHead, xFood, yFood;
    std::tie(xHead,yHead) = snakeHead.getCoord();
    std::tie(xFood,yFood) = food.getCoord();

    return xHead == xFood && yHead == yFood;
}

bool Game::obstacleCollision(SnakePart &snakeHead) {
    float xHead,yHead;
    std::tie(xHead,yHead) = snakeHead.getCoord();
    if (xHead < 0 || yHead < 0 || xHead > 800 || yHead > 600) return true;
    return false;
}

void Game::gameOver() {
    std::cout << "OUCH\n";
    gfx.closeWindow();
}


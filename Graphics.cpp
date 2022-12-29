#include <iostream>
#include "Graphics.h"
#include "Constants.h"

void Graphics::beginFrame() {
    wnd->clear(sf::Color::Black);
}

void Graphics::createWindow(int width, int height, std::string const &title) {
    wnd = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
    wnd->setFramerateLimit(10); //TODO: For Debugging
}

void Graphics::closeWindow() {
    wnd->close();
}

void Graphics::endFrame() {
    wnd->display();
}

bool Graphics::isWindowOpen() const {
    return wnd->isOpen();
}

void Graphics::processWindowEvents() {
    for (sf::Event event{}; wnd->pollEvent(event);) {
        if (event.type == sf::Event::Closed) {
            wnd->close();
        }
    }


}

void Graphics::drawSnake(const Snake &snake) {
    auto snakeBody = snake.getSnakeParts();
    sf::RectangleShape rectangleShape(sf::Vector2f(SNAKE_PART_SIZE, SNAKE_PART_SIZE));
    rectangleShape.setFillColor(sf::Color(SNAKE_COLOR_R, SNAKE_COLOR_G, SNAKE_COLOR_B));
    for (auto snakePart: snakeBody) {
        auto coord = snakePart.getCoord();
        rectangleShape.setPosition(coord.first, coord.second);
        wnd->draw(rectangleShape);
    }
}

void Graphics::drawFood(Food &food) {
    sf::CircleShape shape(FOOD_SIZE);
    shape.setFillColor(sf::Color(FOOD_COLOR_R,FOOD_COLOR_G,FOOD_COLOR_B));
    shape.setPosition(food.getCoord().first, food.getCoord().second);
    wnd->draw(shape);


}

Directions Graphics::updateDirection(Snake &snake) {
    auto dir = snake.getDirection();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && dir != Directions::RIGHT) dir = Directions::LEFT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && dir != Directions::LEFT)dir = Directions::RIGHT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && dir != Directions::DOWN)dir = Directions::UP;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && dir != Directions::UP) dir = Directions::DOWN;
    snake.setDirection(dir);
    snake.updatePosition();
}



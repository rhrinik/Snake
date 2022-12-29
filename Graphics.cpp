#include <iostream>
#include "Graphics.h"

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
    sf::RectangleShape rectangleShape(sf::Vector2f(snake.PART_SIZE, snake.PART_SIZE));
    int R;
    int G;
    int B;
    std::tie(R, G, B) = snake.RGB;
    rectangleShape.setFillColor(sf::Color(R, G, B));
    for (auto snakePart: snakeBody) {
        auto coord = snakePart.getCoord();
        rectangleShape.setPosition(coord.first, coord.second);
        wnd->draw(rectangleShape);
    }
}

void Graphics::drawFood(Food food) {
    sf::CircleShape shape(10);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(food.getCoord().first, food.getCoord().second);
    wnd->draw(shape);


}





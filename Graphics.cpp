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

void Graphics::drawSnake(float x, float y) {
    sf::RectangleShape rectangleShape(sf::Vector2f(SNAKE_PART_SIZE, SNAKE_PART_SIZE));
    rectangleShape.setFillColor(sf::Color(SNAKE_COLOR_R, SNAKE_COLOR_G, SNAKE_COLOR_B));
    rectangleShape.setPosition(x,y);
    wnd->draw(rectangleShape);
}


void Graphics::drawFood(float x, float y) {
    sf::CircleShape shape(FOOD_SIZE);
    shape.setFillColor(sf::Color(FOOD_COLOR_R, FOOD_COLOR_G, FOOD_COLOR_B));
    shape.setPosition(x, y);
    wnd->draw(shape);


}

char Graphics::getKP() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) return 'A';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) return 'D';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) return 'W';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) return 'S';
   return 'X' ;
}



#include "Graphics.h"

void Graphics::beginFrame() {
    wnd.wnd->clear(sf::Color::Black);
}

void Graphics::endFrame() {
    wnd.wnd->display();
}

void Graphics::drawImage(Image &image) {
    image.sprite.setScale(
            static_cast<float>(wnd.wnd->getSize().x) / image.sprite.getLocalBounds().width,
            static_cast<float>(wnd.wnd->getSize().y) / image.sprite.getLocalBounds().height);
    wnd.wnd->draw(image.sprite);
}

void Graphics::drawText(Text &text) {
    wnd.wnd->draw(text.text);
}

void Graphics::drawRectangle(std::pair<int, int> topLeftPoint, std::pair<int, int> bottomRightPoint, Color color) {
    sf::RectangleShape shape({static_cast<float>(bottomRightPoint.first-topLeftPoint.first), static_cast<float>(bottomRightPoint.second - topLeftPoint.second)});
    shape.setPosition({static_cast<float>(topLeftPoint.first),static_cast<float>(topLeftPoint.second)});
    shape.setFillColor(sf::Color(color.r(), color.g(), color.b()));
    wnd.wnd->draw(shape);
}

void Graphics::drawCircle(std::pair<int, int> topLeftPoint, int radius, Color color) {
    sf::CircleShape shape(static_cast<float>(radius));
    shape.setPosition(static_cast<float>(topLeftPoint.first), static_cast<float>(topLeftPoint.second));
    shape.setFillColor(sf::Color(color.r(), color.g(), color.b()));
    wnd.wnd->draw(shape);
}

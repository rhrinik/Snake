#include "Graphics.h"

void Graphics::beginFrame() {
    wnd->clear(sf::Color::Black);
}

void Graphics::createWindow(int width, int height, std::string const& title) {
    windowClosed = false;
    wnd = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
}

void Graphics::closeWindow() {
    wnd->close();
}

void Graphics::endFrame() {
    wnd->display();
}

bool Graphics::isWindowClosed() const {
    return windowClosed;
}

void Graphics::processEvents() {
    for (sf::Event event{};wnd->pollEvent(event);) {
        if (event.type == sf::Event::Closed) {
            wnd->close();
            windowClosed = true;
        }
    }
}

void Graphics::drawImage(Image &image) {
    image.sprite.setScale(
            static_cast<float>(wnd->getSize().x) / image.sprite.getLocalBounds().width,
            static_cast<float>(wnd->getSize().y) / image.sprite.getLocalBounds().height);
    wnd->draw(image.sprite);
}
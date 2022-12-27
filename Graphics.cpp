#include "Graphics.h"

void Graphics::beginFrame() {
    wnd->clear(sf::Color::Black);
}

void Graphics::createWindow() {
    windowClosed = false;
    wnd = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Snake");
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

void Graphics::processWindowEvents() {
    for (sf::Event event{};wnd->pollEvent(event);) {
        if (event.type == sf::Event::Closed) {
            wnd->close();
            windowClosed = true;
        }
    }
}

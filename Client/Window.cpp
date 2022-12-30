#include "Window.h"

void Window::closeWindow() {
    wnd->close();
}

bool Window::isWindowClosed() const {
    return windowClosed;
}

void Window::processEvents() {
    for (sf::Event event{};wnd->pollEvent(event);) {
        switch (event.type) {
            case sf::Event::Closed:
                wnd->close();
                windowClosed = true;
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        keys[Up] = true;
                    case sf::Keyboard::Down:
                        keys[Down] = true;
                    case sf::Keyboard::Left:
                        keys[Left] = true;
                    case sf::Keyboard::Right:
                        keys[Right] = true;
                    default:
                        break;
                }
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        keys[Up] = false;
                    case sf::Keyboard::Down:
                        keys[Down] = false;
                    case sf::Keyboard::Left:
                        keys[Left] = false;
                    case sf::Keyboard::Right:
                        keys[Right] = false;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}
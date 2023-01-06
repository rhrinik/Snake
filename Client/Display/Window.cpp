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
                        for (auto& k : registeredObjects)
                            k.get().onKeyUp();
                        break;
                    case sf::Keyboard::Down:
                        for (auto& k : registeredObjects)
                            k.get().onKeyDown();
                        break;
                    case sf::Keyboard::Left:
                        for (auto& k : registeredObjects)
                            k.get().onKeyLeft();
                        break;
                    case sf::Keyboard::Right:
                        for (auto& k : registeredObjects)
                            k.get().onKeyRight();
                        break;
                    case sf::Keyboard::Enter:
                        for (auto& k : registeredObjects)
                            k.get().onKeyEnter();
                        break;
                    case sf::Keyboard::BackSpace:
                        for (auto& k : registeredObjects)
                            k.get().onBackSpace();
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::TextEntered:
                for (auto& k : registeredObjects)
                    k.get().onTextEntered(static_cast<char>(event.text.unicode));
                break;
            default:
                break;
        }
    }
}

void Window::registerObject(KeyPresses &k) {
    registeredObjects.emplace_back(k);
}

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../Utility/KeyPresses.h"

class Window {
public:
    friend class Graphics;
private:
    std::unique_ptr<sf::RenderWindow> wnd;
    bool windowClosed{true};
    std::vector<std::reference_wrapper<KeyPresses>> registeredObjects;
public:
    Window() = default;
    void createWindow(int width, int height, std::string const& title) {
        windowClosed = false;
        wnd = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);
    }
    [[nodiscard]] std::pair<int,int> getSize() const {
        return {wnd->getSize().x,wnd->getSize().y};
    }
    void closeWindow();
    [[nodiscard]] bool isWindowClosed() const;
    void processEvents();
    void registerObject(KeyPresses& k);
};

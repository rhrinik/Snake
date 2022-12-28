#pragma once
#include <SFML/Graphics.hpp>

class Graphics {
    std::unique_ptr<sf::RenderWindow> wnd;
    bool windowClosed{true};
public:
    void beginFrame();
    void createWindow(int width, int height, std::string const& title);
    void closeWindow();
    void endFrame();
    [[nodiscard]] bool isWindowClosed() const;
    void processEvents();
    //funkcia len na testovanie
    void drawCircle(int x, int y, int radius, int r, int g, int b) {
        sf::CircleShape shape(static_cast<float>(radius));
        shape.setPosition(static_cast<float>(x), static_cast<float>(y));
        shape.setFillColor(sf::Color(r, g, b));
        wnd->draw(shape);
    }
    //funkcia len na testovanie
    auto getMouseCoord() {
        sf::Vector2i position = sf::Mouse::getPosition(*wnd);
        return std::make_pair(position.x, position.y);
    }
};

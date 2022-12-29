#pragma once
#include <SFML/Graphics.hpp>
#include "Color.h"

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
    void drawCircle(std::pair<int,int> topLeftPoint, int radius, Color color) {
        sf::CircleShape shape(static_cast<float>(radius));
        shape.setPosition(static_cast<float>(topLeftPoint.first), static_cast<float>(topLeftPoint.second));
        shape.setFillColor(sf::Color(color.r(), color.g(), color.b()));
        wnd->draw(shape);
    }
    //funkcia len na testovanie
    auto getMouseCoord() {
        sf::Vector2i position = sf::Mouse::getPosition(*wnd);
        return std::make_pair(position.x, position.y);
    }
};

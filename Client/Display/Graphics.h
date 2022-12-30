#pragma once
#include <SFML/Graphics.hpp>
#include "Color.h"
#include "Image.h"
#include "Text.h"
#include "Window.h"

class Graphics {
    //std::unique_ptr<sf::RenderWindow> wnd;
    Window& wnd;
public:
    explicit Graphics(Window &wnd) : wnd(wnd) {}
    void beginFrame();
    void endFrame();
    //funkcia len na testovanie
    void drawCircle(std::pair<int,int> topLeftPoint, int radius, Color color) {
        sf::CircleShape shape(static_cast<float>(radius));
        shape.setPosition(static_cast<float>(topLeftPoint.first), static_cast<float>(topLeftPoint.second));
        shape.setFillColor(sf::Color(color.r(), color.g(), color.b()));
        wnd.wnd->draw(shape);
    }
    //funkcia len na testovanie
    auto getMouseCoord() {
        sf::Vector2i position = sf::Mouse::getPosition(*wnd.wnd);
        return std::make_pair(position.x, position.y);
    }
    void drawImage(Image &image);
    void drawText(Text &text);
    //funkcia len na testovanie
    void drawRectangle(std::pair<int,int> topLeftPoint, std::pair<int,int> bottomRightPoint, Color color) {
        sf::RectangleShape shape({static_cast<float>(bottomRightPoint.first-topLeftPoint.first), static_cast<float>(bottomRightPoint.second - topLeftPoint.second)});
        shape.setPosition({static_cast<float>(topLeftPoint.first),static_cast<float>(topLeftPoint.second)});
        shape.setFillColor(sf::Color(color.r(), color.g(), color.b()));
        wnd.wnd->draw(shape);
    }
};

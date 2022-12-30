#pragma once
#include <SFML/Graphics.hpp>

class Text {
    friend class Graphics;
    sf::Font font;
    sf::Text text;
public:
    Text() = default;
    bool loadFromFile(std::string const& path);
};

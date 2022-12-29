#pragma once
#include <SFML/Graphics.hpp>

class Text {
    friend class Graphics;
    sf::Font font;
public:
    Text() = default;
    bool loadFromFile(std::string const& path);
};

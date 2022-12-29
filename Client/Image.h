#pragma once
#include <SFML/Graphics.hpp>

class Image {
    friend class Graphics;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Image() = default;
    bool loadFromFile(std::string const& path);
};

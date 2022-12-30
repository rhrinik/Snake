#pragma once
#include <SFML/Graphics.hpp>

class Font {
    friend class Text;
    sf::Font font;
public:
    Font() = default;
    bool loadFontFromFile(std::string const& path);
};

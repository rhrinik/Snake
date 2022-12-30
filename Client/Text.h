#pragma once
#include <SFML/Graphics.hpp>

class Text {
    friend class Graphics;
    sf::Font font;
    sf::Text text;
public:
    Text() = default;
    bool loadFontFromFile(std::string const& path);
    void setText(std::string const& str);
    void setSize(std::size_t size);
    void setPosition(std::pair<int,int> pos);
};

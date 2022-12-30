#pragma once
#include <SFML/Graphics.hpp>
#include "Font.h"

class Text {
    friend class Graphics;
    sf::Text text;
public:
    Text() = default;
    void setFont(const Font& newFont);
    void setText(std::string const& str);
    void setSize(std::size_t size);
    void setPosition(std::pair<int,int> pos);
    [[nodiscard]] std::pair<int,int> getSize() const;
};

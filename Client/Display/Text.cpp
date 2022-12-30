#include "Text.h"

void Text::setText(const std::string &str) {
    text.setString(str);
}

void Text::setSize(std::size_t size) {
    text.setCharacterSize(size);
}

void Text::setPosition(std::pair<int, int> pos) {
    text.setPosition(static_cast<float>(pos.first),static_cast<float>(pos.second)-text.getGlobalBounds().top);
}

std::pair<int, int> Text::getSize() const {
    return {text.getGlobalBounds().width, text.getGlobalBounds().height};
}

void Text::setFont(const Font& newFont) {
    text.setFont(newFont.font);
}

std::pair<int, int> Text::getPosition() const {
    return {text.getGlobalBounds().left,text.getGlobalBounds().top};
}

void Text::setOutlineColor(Color color) {
    text.setOutlineColor({color.r(),color.g(),color.b()});
}

void Text::setOutlineSize(std::size_t size) {
    text.setOutlineThickness(static_cast<float>(size));
}

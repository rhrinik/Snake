#include "Text.h"

bool Text::loadFromFile(const std::string &path) {
    if (!font.loadFromFile(path))
        return false;
    text.setFont(font);
    text.setPosition(20,20);
    text.setString("SNAKE");
    text.setCharacterSize(40);
    return true;
}

#include "Text.h"

bool Text::loadFromFile(const std::string &path) {
    return font.loadFromFile("../font.otf");
}

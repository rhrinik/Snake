#include "Color.h"

unsigned char Color::r() const {
    return red;
}

Color &Color::withR(unsigned char r) {
    red = r;
    return *this;
}

unsigned char Color::g() const {
    return green;
}

Color &Color::withG(unsigned char g) {
    green = g;
    return *this;
}

unsigned char Color::b() const {
    return blue;
}

Color &Color::withB(unsigned char b) {
    blue = b;
    return *this;
}

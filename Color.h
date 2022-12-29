#pragma once

class Color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
public:
    Color(unsigned char r, unsigned char g, unsigned char b) : red(r), green(g), blue(b) {}
    Color() : Color(0,0,0) {}
    [[nodiscard]] unsigned char r() const;
    Color& withR(unsigned char r);
    [[nodiscard]] unsigned char g() const;
    Color& withG(unsigned char g);
    [[nodiscard]] unsigned char b() const;
    Color& withB(unsigned char b);
};

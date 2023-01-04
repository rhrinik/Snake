#pragma once

class Color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
public:
    constexpr Color(unsigned char r, unsigned char g, unsigned char b) : red(r), green(g), blue(b) {}
    constexpr Color() : Color(0,0,0) {}
    [[nodiscard]] unsigned char r() const;
    Color& withR(unsigned char r);
    [[nodiscard]] unsigned char g() const;
    Color& withG(unsigned char g);
    [[nodiscard]] unsigned char b() const;
    Color& withB(unsigned char b);
    constexpr Color operator+(Color color) const {
        return {static_cast<unsigned char>(red + color.red),
                static_cast<unsigned char>(green + color.green),
                static_cast<unsigned char>(blue + color.blue)};
    }
};

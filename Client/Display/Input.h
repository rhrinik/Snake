#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Text.h"

class Input : public Text {
    std::string string;
public:
    Input& operator += (char c) {
        string += c;
        Text::setText(string);
        return *this;
    }
    Input& operator--(){
        if (!string.empty())
            string.pop_back();
        Text::setText(string);
        return *this;
    }
    [[nodiscard]] const std::string &getString() const {
        return string;
    }
    void setText(const std::string &str) override {
        string = str;
        Text::setText(str);
    }
    [[nodiscard]] std::string getText() const {
        return string;
    }
};

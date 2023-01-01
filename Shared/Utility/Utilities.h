#pragma once
#include <utility>

inline std::pair<int, int> operator*(std::pair<int, int> p, int x) {
    return {p.first * x, p.second * x};
}

inline std::pair<int, int> operator+(std::pair<int, int> p, std::pair<int, int> p2) {
    return {p.first + p2.first, p.second + p2.second};
}

inline std::pair<int, int>& operator+=(std::pair<int, int>& p, std::pair<int, int> p2) {
    p = {p.first + p2.first, p.second + p2.second};
    return p;
}

inline std::pair<int, int>& operator-=(std::pair<int, int>& p, std::pair<int, int> p2) {
    p = {p.first - p2.first, p.second - p2.second};
    return p;
}

inline std::pair<int, int> operator/(std::pair<int, int> p, int x) {
    return {p.first/x, p.second/x};
}

inline std::pair<int, int> operator-(std::pair<int, int> p, std::pair<int, int> p2) {
    return {p.first - p2.first, p.second - p2.second};
}
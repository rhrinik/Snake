#pragma once
#include <utility>

inline std::pair<int, int> operator*(std::pair<int, int> p, int x) {
    return {p.first * x, p.second * x};
}

inline std::pair<int, int> operator+(std::pair<int, int> p, int x) {
    return {p.first + x, p.second + x};
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

template <typename T>
T remove_at(std::vector<T>&v, typename std::vector<T>::size_type n)
{
    T ans = std::move_if_noexcept(v[n]);
    v[n] = std::move_if_noexcept(v.back());
    v.pop_back();
    return ans;
}
#pragma once
#include <chrono>

class Stopwatch {
    std::chrono::time_point<std::chrono::high_resolution_clock> lastPoint;
    double totalTime{};
public:
    double reset();
    bool removeTime(int seconds);
};


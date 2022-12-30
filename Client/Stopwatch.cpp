#include "Stopwatch.h"

double Stopwatch::reset() {
    using namespace std::chrono;

    auto const timePoint = high_resolution_clock::now();
    duration<double> const elapsed = timePoint - lastPoint;
    lastPoint = timePoint;
    return elapsed.count();
}

bool Stopwatch::removeTime(double seconds) {
    totalTime += reset();
    if (totalTime < seconds)
        return false;
    totalTime -= seconds;
    return true;
}

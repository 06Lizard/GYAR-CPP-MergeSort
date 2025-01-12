#pragma once
#include <chrono>
#include <array>
#include <numeric>
#include <iostream>

class DeltaTimeCounter
{
private:
    static const int sampleSize = 10;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;
    std::array<double, sampleSize> frameTimes;
    int frameIndex;
    double averageDelta;

public:
    DeltaTimeCounter() : lastFrameTime(std::chrono::high_resolution_clock::now()), frameTimes{}, frameIndex(0), averageDelta(0.0)
    {
    }

    void Reset() {
        lastFrameTime = std::chrono::high_resolution_clock::now();
        frameTimes.fill(0.0);
        frameIndex = 0;
        averageDelta = 0.0;
    }

    void Count() {
        using namespace std::chrono;
        auto currentFrameTime = high_resolution_clock::now();
        duration<double> delta = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // store the frameTime to the array
        frameTimes[frameIndex] = delta.count();
        frameIndex = (frameIndex + 1) % frameTimes.size();

        // calculate average frameTime
        averageDelta = std::accumulate(frameTimes.begin(), frameTimes.end(), 0.0) / frameTimes.size();
    }

    void Display(short x, short y) {
        // display deltaTime avrage (ms)
        std::cout << "\033[" << y << ";" << x << "HAverage Frame Time: "
            << (averageDelta > 0.0 ? averageDelta * 1000.0 : 0.0)
            << " ms" << std::endl;
    }

    double GetDelta() const {
        return averageDelta;
    }
};

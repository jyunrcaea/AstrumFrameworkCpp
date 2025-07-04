#pragma once
#include <chrono>
#include "singleton.hpp"

class AstrumChrono : public singleton<AstrumChrono> {
    friend class singleton<AstrumChrono>;

public:
    double DeltaTime() const { return deltaTime; }
    std::chrono::duration<double> RunningTime() const {
        return std::chrono::steady_clock::now() - startTime;
    }

    void SetFramerate(uint16_t value) {
        framerate = value;
        if (framerate != 0) {
            deltaTick = std::chrono::nanoseconds(1'000'000'000) / framerate;
        }
        else {
            deltaTick = std::chrono::nanoseconds(614); // 대체값
        }
    }

    void Initialize() {
        startTime = std::chrono::steady_clock::now();
        lastTick = nextTick = std::chrono::steady_clock::now();
    }

    bool IsUpdateNow() {
        auto current = std::chrono::steady_clock::now();
        if (current < nextTick) return false;

        lastTick = nextTick;
        nextTick += deltaTick;

        if (nextTick < current) nextTick = current + deltaTick;

        deltaTime = std::chrono::duration<double>(nextTick - lastTick).count();
        return true;
    }

    void Dispose() {
        // nothing to dispose
    }

private:
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point lastTick;
    std::chrono::steady_clock::time_point nextTick;
    std::chrono::nanoseconds deltaTick = std::chrono::nanoseconds(614);
    uint16_t framerate = 0;
    double deltaTime = 0.0;
};

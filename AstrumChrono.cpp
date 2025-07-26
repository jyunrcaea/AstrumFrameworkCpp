#include "AstrumChrono.hpp"

double AstrumChronoSingleton::GetDeltaTime() const {
    return deltaTime;
}

std::chrono::duration<double> AstrumChronoSingleton::GetRunningTime() const {
    return std::chrono::steady_clock::now() - startTime;
}

void AstrumChronoSingleton::SetFramerate(uint16_t value) {
    framerate = value;
    if (framerate != 0) {
        deltaTick = std::chrono::nanoseconds(1'000'000'000) / framerate;
    }
    else {
        deltaTick = std::chrono::nanoseconds(614);
    }
}

void AstrumChronoSingleton::Initialize() {
    startTime = std::chrono::steady_clock::now();
    lastTick = nextTick = std::chrono::steady_clock::now();
}

bool AstrumChronoSingleton::IsUpdateNow() {
    auto current = std::chrono::steady_clock::now();
    if (current < nextTick) return false;

    lastTick = nextTick;
    nextTick += deltaTick;

    if (nextTick < current) nextTick = current + deltaTick;

    deltaTime = std::chrono::duration<double>(nextTick - lastTick).count();
    return true;
}

void AstrumChronoSingleton::Dispose() {
    // nothing to dispose
}
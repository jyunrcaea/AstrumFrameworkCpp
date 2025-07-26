#pragma once
#include <chrono>
#include "singleton.hpp"

class AstrumChronoSingleton : public Singleton<AstrumChronoSingleton> {
    friend class Singleton<AstrumChronoSingleton>;
    friend class AstrumChrono;

    double GetDeltaTime() const;
    std::chrono::duration<double> GetRunningTime() const;
    void SetFramerate(uint16_t value);
    void Initialize();
    bool IsUpdateNow();
    void Dispose();

private:
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point lastTick;
    std::chrono::steady_clock::time_point nextTick;
    std::chrono::nanoseconds deltaTick = std::chrono::nanoseconds(10);
    uint16_t framerate = 0;
    double deltaTime = 0.0;
};

class AstrumChrono {
public:
    static inline double GetDeltaTime() { return AstrumChronoSingleton::Instance().GetDeltaTime(); }
    static inline std::chrono::duration<double> GetRunningTime() { AstrumChronoSingleton::Instance().GetRunningTime(); }
    static inline void SetFramerate(uint16_t value) { AstrumChronoSingleton::Instance().SetFramerate(value); }
    static inline void Initialize() { AstrumChronoSingleton::Instance().Initialize(); }
    static inline bool IsUpdateNow() { return AstrumChronoSingleton::Instance().IsUpdateNow(); }
    static inline void Dispose() { AstrumChronoSingleton::Instance().Dispose(); }
};
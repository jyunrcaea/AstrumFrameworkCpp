#pragma once
#include <chrono>
#include "AstrumSingleton.hpp"

class AstrumChronoSingleton : public AstrumSingleton<AstrumChronoSingleton> {
    friend class AstrumSingleton<AstrumChronoSingleton>;
    friend class AstrumChrono;

    /// <summary>
    /// 이전 프레임 이후 경과한 시간(초)을 반환합니다.
    /// </summary>
    /// <returns>델타 시간(초)입니다.</returns>
    double GetDeltaTime() const;
    /// <summary>
    /// 프로그램 시작 이후 경과한 시간을 반환합니다.
    /// </summary>
    /// <returns>프로그램 실행 시간입니다.</returns>
    std::chrono::duration<double> GetRunningTime() const;
    /// <summary>
    /// 프레임 레이트를 설정합니다.
    /// </summary>
    /// <param name="value">설정할 프레임 레이트(초당 프레임 수)입니다.</param>
    void SetFramerate(uint16_t value);
    /// <summary>
    /// 시간 관리 시스템을 초기화합니다.
    /// </summary>
    void Initialize();
    /// <summary>
    /// 설정된 프레임 레이트에 따라 이 순간이 업데이트 시점인지 확인합니다.
    /// </summary>
    /// <returns>업데이트해야 하면 true, 아니면 false를 반환합니다.</returns>
    bool IsUpdateNow();
    /// <summary>
    /// 시간 관리 시스템을 정리하고 해제합니다.
    /// </summary>
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
    AstrumChrono() = delete;
public:
	/// <summary>
	/// 현재 시간을 나노초 단위의 정수로 반환합니다.
	/// </summary>
	/// <returns>현재 시간(나노초)입니다.</returns>
	static inline long long GetNow() { return std::chrono::steady_clock::now().time_since_epoch().count(); }
    /// <summary>
    /// 이전 프레임 이후 경과한 시간(초)을 반환합니다.
    /// </summary>
    /// <returns>델타 시간(초)입니다.</returns>
    static inline double GetDeltaTime() { return AstrumChronoSingleton::Instance().GetDeltaTime(); }
    /// <summary>
    /// 프로그램 시작 이후 경과한 시간(초)을 반환합니다.
    /// </summary>
    /// <returns>프로그램 실행 시간(초)입니다.</returns>
    static inline double GetRunningTime() { auto duration = AstrumChronoSingleton::Instance().GetRunningTime(); return duration.count(); }
    /// <summary>
    /// 프레임 레이트를 설정합니다.
    /// </summary>
    /// <param name="value">설정할 프레임 레이트(초당 프레임 수)입니다.</param>
    static inline void SetFramerate(uint16_t value) { AstrumChronoSingleton::Instance().SetFramerate(value); }
    /// <summary>
    /// 시간 관리 시스템을 초기화합니다.
    /// </summary>
    static inline void Initialize() { AstrumChronoSingleton::Instance().Initialize(); }
    /// <summary>
    /// 설정된 프레임 레이트에 따라 이 순간이 업데이트 시점인지 확인합니다.
    /// </summary>
    /// <returns>업데이트해야 하면 true, 아니면 false를 반환합니다.</returns>
    static inline bool IsUpdateNow() { return AstrumChronoSingleton::Instance().IsUpdateNow(); }
    /// <summary>
    /// 시간 관리 시스템을 정리하고 해제합니다.
    /// </summary>
    static inline void Dispose() { AstrumChronoSingleton::Instance().Dispose(); }
};
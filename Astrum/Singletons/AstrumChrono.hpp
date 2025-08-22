#pragma once
#include <chrono>
#include "AstrumSingleton.hpp"

namespace Astrum
{
	class ChronoSingleton : public Singleton<ChronoSingleton> {
		friend class Singleton<ChronoSingleton>;
		friend class Chrono;

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

	class Chrono {
		Chrono() = delete;
	public:
		static inline double GetDeltaTime() { return ChronoSingleton::Instance().GetDeltaTime(); }
		static inline double GetRunningTime() { auto duration = ChronoSingleton::Instance().GetRunningTime(); return duration.count(); }
		static inline void SetFramerate(uint16_t value) { ChronoSingleton::Instance().SetFramerate(value); }
		static inline void Initialize() { ChronoSingleton::Instance().Initialize(); }
		static inline bool IsUpdateNow() { return ChronoSingleton::Instance().IsUpdateNow(); }
		static inline void Dispose() { ChronoSingleton::Instance().Dispose(); }
	};
}
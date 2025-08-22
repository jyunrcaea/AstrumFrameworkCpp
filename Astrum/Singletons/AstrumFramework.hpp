#pragma once
#include <windows.h>
#include <memory>
#include <string>
#include <cstdint>
#include "../Objects/AstrumGroupObject.hpp"
#include "AstrumSingleton.hpp"

namespace Astrum {
	class Framework;

	class FrameworkSingleton : public Singleton<FrameworkSingleton> {
		friend class Singleton<FrameworkSingleton>;
		friend class Framework;
		FrameworkSingleton();

	private:
		bool IsInitialized() const;
		bool IsRunning() const;
		void Initialize(const std::wstring& title = L"Astrum Framework", unsigned int width = 1280, unsigned int height = 720);
		int Run();
		void Stop();
		std::shared_ptr<GroupObject> RootObject = std::make_shared<GroupObject>();

	private:
		bool isRunning = false;
		void Prepare();
		void Update();
		void Release();
	};

	class Framework {
		Framework() = delete;
	public:
		static inline bool IsInitialized() { return FrameworkSingleton::Instance().IsInitialized(); }
		static inline bool IsRunning() { return FrameworkSingleton::Instance().IsRunning(); }
		static inline void Initialize(const std::wstring& title = L"Astrum Framework", unsigned int width = 1280, unsigned int height = 720) { FrameworkSingleton::Instance().Initialize(title, width, height); }
		static inline int Run() { return FrameworkSingleton::Instance().Run(); }
		static inline void Stop() { return FrameworkSingleton::Instance().Stop(); }
		static inline std::shared_ptr<GroupObject> GetRootObject() { return FrameworkSingleton::Instance().RootObject; }
		static inline void SetRootObject(const std::shared_ptr<GroupObject>& obj) { FrameworkSingleton::Instance().RootObject = obj; }
	};
}
#pragma once
#include <windows.h>
#include <memory>
#include <string>
#include <cstdint>
#include "AstrumGroupObject.hpp"
#include "AstrumSingleton.hpp"

class AstrumFrameworkSingleton : public AstrumSingleton<AstrumFrameworkSingleton> {
    friend class AstrumSingleton<AstrumFrameworkSingleton>;
    friend class AstrumFramework;
public:
    bool IsInitialized() const;
    bool IsRunning() const;
    void Initialize(const std::wstring& title = L"Astrum Framework", unsigned int width = 1280, unsigned int height = 720);
    int Run();
    void Stop();
    std::shared_ptr<AstrumGroupObject> RootObject = std::make_shared<AstrumGroupObject>();
private:
    AstrumFrameworkSingleton();
    bool isRunning = false;
    void Prepare();
    void Update();
    void Release();
};

class AstrumFramework {
    AstrumFramework() = delete;
public:
    static inline bool IsInitialized() { return AstrumFrameworkSingleton::Instance().IsInitialized(); }
    static inline bool IsRunning() { return AstrumFrameworkSingleton::Instance().IsRunning(); }
    static inline void Initialize(const std::wstring& title = L"Astrum Framework", unsigned int width = 1280, unsigned int height = 720) { AstrumFrameworkSingleton::Instance().Initialize(title, width, height); }
    static inline int Run() { return AstrumFrameworkSingleton::Instance().Run(); }
    static inline void Stop() { AstrumFrameworkSingleton::Instance().Stop(); }
    static inline std::shared_ptr<AstrumGroupObject> GetRootObject() { return AstrumFrameworkSingleton::Instance().RootObject; }
    static inline void SetRootObject(const std::shared_ptr<AstrumGroupObject>& obj) { AstrumFrameworkSingleton::Instance().RootObject = obj; }
};
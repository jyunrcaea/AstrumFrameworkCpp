#pragma once
#include <windows.h>
#include <memory>
#include <string>
#include <cstdint>
#include "AstrumGroupObject.hpp"
#include "singleton.hpp"

class AstrumFramework : public Singleton<AstrumFramework> {
    friend class Singleton<AstrumFramework>;

public:
    bool IsInitialized() const;
    bool IsRunning() const;

    void Initialize(const std::wstring& title = L"Astrum Framework", unsigned int width = 1280, unsigned int height = 720);

    int Run();
    void Stop();

    std::shared_ptr<AstrumGroupObject> RootObject = std::make_shared<AstrumGroupObject>();

private:
    AstrumFramework();

    bool isRunning = false;

    void Prepare();
    void Update();
    void Release();
};
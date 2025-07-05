#pragma once
#include <windows.h>
#include <memory>
#include <string>
#include <cstdint>
#include "AstrumWindow.hpp"
#include "AstrumRenderer.hpp"
#include "AstrumDirectInput.hpp"
#include "AstrumChrono.hpp"
#include "AstrumException.hpp"
#include "AstrumGroupObject.hpp"
#include "singleton.hpp"

class Framework : public singleton<Framework> {
    friend class singleton<Framework>;

public:
    bool IsInitialized() const;
    bool IsRunning() const;

    void Initialize(const std::wstring& title = L"Astrum Framework",
        uint16_t width = 1280,
        uint16_t height = 720);

    int  Run();
    void Stop();

    std::shared_ptr<AstrumGroupObject> RootObject;

private:
    Framework();

    bool isRunning;

    void Prepare();
    void Update();
    void Release();
};
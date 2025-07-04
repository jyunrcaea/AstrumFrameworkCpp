#pragma once

#include "singleton.hpp"
#include "AstrumWindow.hpp"

#include <dinput.h>
#include <cstdint>

class AstrumDirectInput : public singleton<AstrumDirectInput> {
    friend class singleton<AstrumDirectInput>;

public:
    bool Initialize();
    void Update();
    void Dispose();

    bool IsKeyPressed(uint8_t vk) const;

private:
    HRESULT SetCooperative(IDirectInputDevice8* dev);

    IDirectInput8* dinput = nullptr;
    IDirectInputDevice8* keyboard = nullptr;
    IDirectInputDevice8* mouse = nullptr;

    BYTE                     keyState[256]{};
    DIMOUSESTATE             mouseState{};
};
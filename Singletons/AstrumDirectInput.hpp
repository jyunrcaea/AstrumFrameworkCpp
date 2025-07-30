#pragma once
#include <dinput.h>
#include <cstdint>
#include <windows.h>
#include <wrl/client.h>
#include "AstrumSingleton.hpp"
#include "AstrumWindow.hpp"
#include "../AstrumException.hpp"

struct AstrumMousePosition {
    long X;
    long Y;
};

class AstrumDirectInputSingleton : public AstrumSingleton<AstrumDirectInputSingleton> {
    friend class AstrumSingleton<AstrumDirectInputSingleton>;
    friend class AstrumDirectInput;

    bool Initialize();
    void Prepare();
    void Update();
    void Release();
    void Dispose();

    bool IsKeyPressed(uint8_t vk) const;
    bool IsKeyReleased(uint8_t vk) const;
    bool WasKeyPressed(uint8_t vk) const;
    bool WasKeyReleased(uint8_t vk) const;

    AstrumMousePosition GetMousePosition() const;
    bool IsMouseButtonPressed(uint8_t button) const;
    long GetMouseWheelDelta() const;

    bool IsEnable() const { return isAcquire; }
    bool IsInitialized() const { return dinput; }
private:
    AstrumDirectInputSingleton();
    HRESULT SetCooperative(IDirectInputDevice8* dev);

    Microsoft::WRL::ComPtr<IDirectInput8> dinput = nullptr;
    Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard = nullptr;
    Microsoft::WRL::ComPtr<IDirectInputDevice8> mouse = nullptr;

    BYTE keyState[256]{};
    BYTE previousKeyState[256]{};
    DIMOUSESTATE mouseState{};

    bool isAcquire = false;
};

class AstrumDirectInput {
    AstrumDirectInput() = delete;

public:
    static inline bool Initialize() { return AstrumDirectInputSingleton::Instance().Initialize(); }
    static inline void Prepare() { AstrumDirectInputSingleton::Instance().Prepare(); }
    static inline void Update() { AstrumDirectInputSingleton::Instance().Update(); }
    static inline void Release() { AstrumDirectInputSingleton::Instance().Release(); }
    static inline void Dispose() { AstrumDirectInputSingleton::Instance().Dispose(); }

    static inline bool IsKeyPressed(uint8_t vk) { return AstrumDirectInputSingleton::Instance().IsKeyPressed(vk); }
    static inline bool IsKeyReleased(uint8_t vk) { return AstrumDirectInputSingleton::Instance().IsKeyReleased(vk); }
    static inline bool WasKeyPressed(uint8_t vk) { return AstrumDirectInputSingleton::Instance().WasKeyPressed(vk); }
    static inline bool WasKeyReleased(uint8_t vk) { return AstrumDirectInputSingleton::Instance().WasKeyReleased(vk); }

    static inline AstrumMousePosition GetMousePosition() { return AstrumDirectInputSingleton::Instance().GetMousePosition(); }
    static inline bool IsMouseButtonPressed(uint8_t button) { return AstrumDirectInputSingleton::Instance().IsMouseButtonPressed(button); }
    static inline long GetMouseWheelDelta() { return AstrumDirectInputSingleton::Instance().GetMouseWheelDelta(); }

    static inline bool IsEnable() { return AstrumDirectInputSingleton::Instance().IsEnable(); }
    static inline bool IsInitialized() { return AstrumDirectInputSingleton::Instance().IsInitialized(); }
};
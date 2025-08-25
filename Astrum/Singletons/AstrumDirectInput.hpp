#pragma once
#include <dinput.h>
#include <cstdint>
#include <windows.h>
#include <wrl/client.h>
#include "AstrumSingleton.hpp"
#include "AstrumWindow.hpp"
#include "../AstrumException.hpp"

enum AstrumMouseButtonType
{
    AstrumMouseButtonType_Left = 0,
    AstrumMouseButtonType_Right,
    AstrumMouseButtonType_Center,
    AstrumMouseButtonType_Last,
};

class AstrumDirectInputSingleton : public AstrumSingleton<AstrumDirectInputSingleton> {
    friend class AstrumSingleton<AstrumDirectInputSingleton>;
    friend class AstrumDirectInput;

    AstrumDirectInputSingleton();
private:
    bool Initialize();
    void Prepare();
    void Update();
    void Release();
    void Dispose();

    bool IsKeyPressed(uint8_t vk) const;
    bool IsKeyReleased(uint8_t vk) const;
    bool WasKeyPressed(uint8_t vk) const;
    bool WasKeyReleased(uint8_t vk) const;

    AstrumVector2 GetMousePosition() const;
    bool IsMouseKeyPressed(AstrumMouseButtonType button) const;
    long GetMouseWheelDelta() const;

    bool IsEnable() const { return isAcquire; }
    bool IsInitialized() const { return dinput; }

    AstrumVector2 GetMouseMovement() const;
private:
    void UpdateMousePosition();
    HRESULT SetCooperative(IDirectInputDevice8* dev);

    Microsoft::WRL::ComPtr<IDirectInput8> dinput = nullptr;
    Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard = nullptr;
    Microsoft::WRL::ComPtr<IDirectInputDevice8> mouse = nullptr;

    BYTE keyState[256]{};
    BYTE previousKeyState[256]{};
    DIMOUSESTATE mouseState{};

    AstrumVector2 mouseMovement;
    AstrumVector2 mousePosition;
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

    static inline AstrumVector2 GetMousePosition() { return AstrumDirectInputSingleton::Instance().GetMousePosition(); }
    static inline bool IsMouseKeyPressed(AstrumMouseButtonType button) { return AstrumDirectInputSingleton::Instance().IsMouseKeyPressed(button); }
    static inline long GetMouseWheelDelta() { return AstrumDirectInputSingleton::Instance().GetMouseWheelDelta(); }

    static inline bool IsEnable() { return AstrumDirectInputSingleton::Instance().IsEnable(); }
    static inline bool IsInitialized() { return AstrumDirectInputSingleton::Instance().IsInitialized(); }

    static inline AstrumVector2 GetMouseMovement() { return AstrumDirectInputSingleton::Instance().GetMouseMovement(); }
};
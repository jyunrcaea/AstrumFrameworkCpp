#include "AstrumDirectInput.hpp"
#include "AstrumException.hpp"  // if you wish to throw exceptions
#include <windows.h>

bool AstrumDirectInput::Initialize() {
    if (FAILED(DirectInput8Create(
        GetModuleHandle(nullptr),
        DIRECTINPUT_VERSION,
        IID_IDirectInput8,
        reinterpret_cast<void**>(&dinput),
        nullptr)))
    {
        return false;
    }

    // Keyboard
    if (FAILED(dinput->CreateDevice(GUID_SysKeyboard, &keyboard, nullptr))) return false;
    if (FAILED(keyboard->SetDataFormat(&c_dfDIKeyboard))) return false;
    if (FAILED(SetCooperative(keyboard))) return false;
    if (FAILED(keyboard->Acquire())) return false;

    // Mouse
    if (FAILED(dinput->CreateDevice(GUID_SysMouse, &mouse, nullptr))) return false;
    if (FAILED(mouse->SetDataFormat(&c_dfDIMouse))) return false;
    if (FAILED(SetCooperative(mouse))) return false;
    if (FAILED(mouse->Acquire())) return false;

    return true;
}

void AstrumDirectInput::Update() {
    if (keyboard) keyboard->GetDeviceState(sizeof(keyState), keyState);
    if (mouse)    mouse->GetDeviceState(sizeof(mouseState), &mouseState);
}

void AstrumDirectInput::Dispose() {
    if (keyboard) {
        keyboard->Unacquire();
        keyboard->Release();
        keyboard = nullptr;
    }
    if (mouse) {
        mouse->Unacquire();
        mouse->Release();
        mouse = nullptr;
    }
    if (dinput) {
        dinput->Release();
        dinput = nullptr;
    }
}

bool AstrumDirectInput::IsKeyPressed(uint8_t vk) const {
    return (keyState[vk] & 0x80) != 0;
}

HRESULT AstrumDirectInput::SetCooperative(IDirectInputDevice8* dev) {
    HWND hwnd = AstrumWindow::Instance().GetHandle();
    DWORD flags = AstrumWindow::Instance().IsFullscreen()
        ? (DISCL_FOREGROUND | DISCL_EXCLUSIVE)
        : (DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
    return dev->SetCooperativeLevel(hwnd, flags);
}
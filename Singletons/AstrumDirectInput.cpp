#include "../Singletons/AstrumDirectInput.hpp"

constexpr DWORD DirectInputVersion = 0x0800;

AstrumDirectInputSingleton::AstrumDirectInputSingleton() { }

bool AstrumDirectInputSingleton::Initialize() {
    if (FAILED(DirectInput8Create(
        GetModuleHandle(nullptr),
        DirectInputVersion,
        IID_IDirectInput8,
        reinterpret_cast<void**>(dinput.GetAddressOf()),
        nullptr)))
    {
        return false;
    }

    // Keyboard
    if (FAILED(dinput->CreateDevice(GUID_SysKeyboard, &keyboard, nullptr))) return false;
    if (FAILED(keyboard->SetDataFormat(&c_dfDIKeyboard))) return false;
    if (FAILED(SetCooperative(keyboard.Get()))) return false;

    // Mouse
    if (FAILED(dinput->CreateDevice(GUID_SysMouse, &mouse, nullptr))) return false;
    if (FAILED(mouse->SetDataFormat(&c_dfDIMouse))) return false;
    if (FAILED(SetCooperative(mouse.Get()))) return false;

    if (isAcquire) Prepare();

    return true;
}

// 창 포커스 얻을때도 호출될 함수
void AstrumDirectInputSingleton::Prepare() {
    if (keyboard) keyboard->Acquire(); //습득하고
    if (mouse) mouse->Acquire();
	isAcquire = true;
}

// 함수 만든이유 : 창 포커스 잃을때 키 입력 안들어오게 할려고
void AstrumDirectInputSingleton::Release() {
    if (isAcquire) {
        std::memset(keyState, 0, sizeof(keyState));
		mouseState = {};
    }
    isAcquire = false;

    if (keyboard) keyboard->Unacquire(); //해제하고
    if (mouse) mouse->Unacquire();
}

void AstrumDirectInputSingleton::Update() {
    if (!isAcquire) return;

    memcpy(previousKeyState, keyState, sizeof(keyState));
    if (keyboard) keyboard->GetDeviceState(sizeof(keyState), keyState);
    if (mouse) mouse->GetDeviceState(sizeof(mouseState), &mouseState);
}

void AstrumDirectInputSingleton::Dispose() {
    Release();

    keyboard.Reset();
    mouse.Reset();
    dinput.Reset();
}

bool AstrumDirectInputSingleton::IsKeyPressed(uint8_t vk) const {
    return (keyState[vk] & 0x80) != 0;
}

bool AstrumDirectInputSingleton::IsKeyReleased(uint8_t vk) const {
    return (keyState[vk] & 0x80) == 0;
}

bool AstrumDirectInputSingleton::WasKeyPressed(uint8_t vk) const {
    return (previousKeyState[vk] & 0x80) != 0 && (keyState[vk] & 0x80) == 0;
}

bool AstrumDirectInputSingleton::WasKeyReleased(uint8_t vk) const {
    return (previousKeyState[vk] & 0x80) == 0 && (keyState[vk] & 0x80) != 0;
}

AstrumMousePosition AstrumDirectInputSingleton::GetMousePosition() const {
    return { mouseState.lX, mouseState.lY };
}

bool AstrumDirectInputSingleton::IsMouseButtonPressed(uint8_t button) const {
    if (button < 4) {
        return (mouseState.rgbButtons[button] & 0x80) != 0;
    }
    return false; // Handle invalid button index
}

long AstrumDirectInputSingleton::GetMouseWheelDelta() const {
    return mouseState.lZ;
}

HRESULT AstrumDirectInputSingleton::SetCooperative(IDirectInputDevice8* dev) {
    HWND hwnd = AstrumWindow::GetHandle();
    DWORD flags = AstrumWindow::IsFullscreen()
        ? (DISCL_FOREGROUND | DISCL_EXCLUSIVE)
        : (DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
    return dev->SetCooperativeLevel(hwnd, flags);
}
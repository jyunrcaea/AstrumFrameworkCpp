#include "AstrumDirectInput.hpp"
#include "AstrumRenderer.hpp"

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

    UpdateMousePosition(); // 첫 프레임의 mouseMovement를 무시하기 위해
}

void AstrumDirectInputSingleton::Update() {
    if (!isAcquire) return;

    memcpy(previousKeyState, keyState, sizeof(keyState));
    if (keyboard) keyboard->GetDeviceState(sizeof(keyState), keyState);
    if (mouse) mouse->GetDeviceState(sizeof(mouseState), &mouseState);

    UpdateMousePosition();
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

void AstrumDirectInputSingleton::Dispose() {
    Release();

    keyboard.Reset();
    mouse.Reset();
    dinput.Reset();
}

bool AstrumDirectInputSingleton::IsKeyPressed(uint8_t vk) const { return (keyState[vk] & 0x80) != 0; }
bool AstrumDirectInputSingleton::IsKeyReleased(uint8_t vk) const { return (keyState[vk] & 0x80) == 0; }
bool AstrumDirectInputSingleton::WasKeyPressed(uint8_t vk) const { return (previousKeyState[vk] & 0x80) != 0 && (keyState[vk] & 0x80) == 0; }
bool AstrumDirectInputSingleton::WasKeyReleased(uint8_t vk) const { return (previousKeyState[vk] & 0x80) == 0 && (keyState[vk] & 0x80) != 0; }
AstrumVector2 AstrumDirectInputSingleton::GetMouseMovement() const { return mouseMovement; }
AstrumVector2 AstrumDirectInputSingleton::GetMousePosition() const { return mousePosition; }

bool AstrumDirectInputSingleton::IsMouseKeyPressed(AstrumMouseButtonType button) const {
    if (0 <= button && button < 4) {
        return (mouseState.rgbButtons[static_cast<int>(button)] & 0x80) != 0;
    }
    return false; // out of index
}

long AstrumDirectInputSingleton::GetMouseWheelDelta() const {
    return mouseState.lZ;
}

void AstrumDirectInputSingleton::UpdateMousePosition() {
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(AstrumWindow::GetHandle(), &point);

    auto resolution = AstrumRenderer::Instance().GetResolution();
    AstrumVector2 newMousePos{ 
        static_cast<float>(point.x),
        static_cast<float>(point.y)
    };
    newMousePos *= AstrumRenderer::Instance().GetRSRate();
    newMousePos.Y = resolution.Height - newMousePos.Y;

    mouseMovement = newMousePos - mousePosition;
    mousePosition = newMousePos;

    // How to?
    //FVector3D worldPos = scene->GetCameraManager()->GetCameraWorldPos();

    //MouseWorldPos.x = worldPos.x + MousePos.x - rs.Width * 0.5;
    //MouseWorldPos.y = worldPos.y + MousePos.y - rs.Height * 0.5;
}

HRESULT AstrumDirectInputSingleton::SetCooperative(IDirectInputDevice8* dev) {
    HWND hwnd = AstrumWindow::GetHandle();
    DWORD flags = AstrumWindow::IsFullscreen()
        ? (DISCL_FOREGROUND | DISCL_EXCLUSIVE)
        : (DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
    return dev->SetCooperativeLevel(hwnd, flags);
}
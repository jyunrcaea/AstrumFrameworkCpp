#include "AstrumDirectInput.hpp"
#include "AstrumRenderer.hpp"

namespace Astrum {
	constexpr DWORD DirectInputVersion = 0x0800;

	DirectInputSingleton::DirectInputSingleton() { }

	bool DirectInputSingleton::Initialize() {
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
	void DirectInputSingleton::Prepare() {
		if (keyboard) keyboard->Acquire(); //습득하고
		if (mouse) mouse->Acquire();
		isAcquire = true;

		UpdateMousePosition(); // 첫 프레임의 mouseMovement를 무시하기 위해
	}

	void DirectInputSingleton::Update() {
		if (!isAcquire) return;

		memcpy(previousKeyState, keyState, sizeof(keyState));
		if (keyboard) keyboard->GetDeviceState(sizeof(keyState), keyState);
		if (mouse) mouse->GetDeviceState(sizeof(mouseState), &mouseState);

		UpdateMousePosition();
	}

	// 함수 만든이유 : 창 포커스 잃을때 키 입력 안들어오게 할려고
	void DirectInputSingleton::Release() {
		if (isAcquire) {
			std::memset(keyState, 0, sizeof(keyState));
			mouseState = {};
		}
		isAcquire = false;

		if (keyboard) keyboard->Unacquire(); //해제하고
		if (mouse) mouse->Unacquire();
	}

	void DirectInputSingleton::Dispose() {
		Release();

		keyboard.Reset();
		mouse.Reset();
		dinput.Reset();
	}

	bool DirectInputSingleton::IsKeyPressed(uint8_t vk) const { return (keyState[vk] & 0x80) != 0; }
	bool DirectInputSingleton::IsKeyReleased(uint8_t vk) const { return (keyState[vk] & 0x80) == 0; }
	bool DirectInputSingleton::WasKeyPressed(uint8_t vk) const { return (previousKeyState[vk] & 0x80) != 0 && (keyState[vk] & 0x80) == 0; }
	bool DirectInputSingleton::WasKeyReleased(uint8_t vk) const { return (previousKeyState[vk] & 0x80) == 0 && (keyState[vk] & 0x80) != 0; }
	Vector2 DirectInputSingleton::GetMouseMovement() const { return mouseMovement; }
	Vector2 DirectInputSingleton::GetMousePosition() const { return mousePosition; }

	bool DirectInputSingleton::IsMouseKeyPressed(MouseButtonType button) const {
		if (0 <= button && button < 4) {
			return (mouseState.rgbButtons[static_cast<int>(button)] & 0x80) != 0;
		}
		return false; // out of index
	}

	long DirectInputSingleton::GetMouseWheelDelta() const {
		return mouseState.lZ;
	}

	void DirectInputSingleton::UpdateMousePosition() {
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(Window::GetHandle(), &point);

		auto resolution = Renderer::Instance().GetResolution();
		Vector2 newMousePos{
			static_cast<float>(point.x),
			static_cast<float>(point.y)
		};
		newMousePos *= Renderer::Instance().GetRSRate();
		newMousePos.Y = resolution.Height - newMousePos.Y;

		mouseMovement = newMousePos - mousePosition;
		mousePosition = newMousePos;

		// How to?
		//FVector3D worldPos = scene->GetCameraManager()->GetCameraWorldPos();

		//MouseWorldPos.x = worldPos.x + MousePos.x - rs.Width * 0.5;
		//MouseWorldPos.y = worldPos.y + MousePos.y - rs.Height * 0.5;
	}

	HRESULT DirectInputSingleton::SetCooperative(IDirectInputDevice8* dev) {
		HWND hwnd = Window::GetHandle();
		DWORD flags = Window::IsFullscreen()
			? (DISCL_FOREGROUND | DISCL_EXCLUSIVE)
			: (DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
		return dev->SetCooperativeLevel(hwnd, flags);
	}
}
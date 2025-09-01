#include "AstrumRawInput.hpp"
#include <string>
#include <format>
#include <windows.h>
#include "AstrumWindow.hpp"
#include "AstrumChrono.hpp"
#include "AstrumRenderer.hpp"

void AstrumRawInputSingleton::Initialize() {
	RAWINPUTDEVICE rid[2];
	rid[0].usUsagePage = 0x01; // Generic Desktop Controls
	rid[0].usUsage = 0x06;     // Keyboard
	rid[0].dwFlags = 0;
	rid[0].hwndTarget = AstrumWindow::GetHandle();

	rid[1].usUsagePage = 0x01; // Generic Desktop Controls
	rid[1].usUsage = 0x02;     // Mouse
	rid[1].dwFlags = 0;        // 포커스가 있을 때만 메시지 수신
	rid[1].hwndTarget = AstrumWindow::GetHandle();

	if (false == RegisterRawInputDevices(rid, 2, sizeof(RAWINPUTDEVICE))) {
		throw AstrumException(std::format("Failed to register raw input device. Error code: {}", GetLastError()));
	}
}

void AstrumRawInputSingleton::Update() {
	//이전 상태 갱신 및 보존
	memcpy(previousKeyState, keyState, sizeof(keyState));
	memcpy(previousMouseState, mouseState, sizeof(mouseState));

	mouseMovement = { 0.0f, 0.0f };
	mouseState[AstrumMouseButtonType_ScrollUp] = false;
	mouseState[AstrumMouseButtonType_ScrollDown] = false;

	UpdateMousePosition();
}

void AstrumRawInputSingleton::Enqueue(const RAWINPUT& raw) {
	if (RIM_TYPEKEYBOARD == raw.header.dwType) {
		EnqueueKeyboard(raw.data.keyboard);
	}
	else if (RIM_TYPEMOUSE == raw.header.dwType) {
		EnqueueMouse(raw.data.mouse);
	}
}

void AstrumRawInputSingleton::EnqueueKeyboard(const RAWKEYBOARD& keyboard) {
	if (keyboard.MakeCode == 0xFF) return;

	bool isPressed = 0 == (keyboard.Flags & RI_KEY_BREAK);
	//중복 입력 방지
	if (keyState[keyboard.VKey] == isPressed) return;
	keyState[keyboard.VKey] = isPressed;
	// 큐 추가
	keyQueue.emplace_back(
		keyboard.VKey,
		keyboard.MakeCode,
		isPressed,
		AstrumChrono::GetRunningTime()
	);
}

void AstrumRawInputSingleton::EnqueueMouse(const RAWMOUSE& mouse) {
	// 상대 이동량 누적
	mouseMovement.X += static_cast<double>(mouse.lLastX);
	mouseMovement.Y += static_cast<double>(mouse.lLastY);

	// 버튼 상태 갱신
	if (mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN)   mouseState[AstrumMouseButtonType_Left] = true;
	if (mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP)     mouseState[AstrumMouseButtonType_Left] = false;
	if (mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN)  mouseState[AstrumMouseButtonType_Right] = true;
	if (mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP)    mouseState[AstrumMouseButtonType_Right] = false;
	if (mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN) mouseState[AstrumMouseButtonType_Center] = true;
	if (mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP)   mouseState[AstrumMouseButtonType_Center] = false;

	// 마우스 휠 처리
	if (mouse.usButtonFlags & RI_MOUSE_WHEEL) {
		short wheelDelta = static_cast<short>(mouse.usButtonData);
		if (wheelDelta > 0) {
			mouseState[AstrumMouseButtonType_ScrollUp] = true;
		}
		else if (wheelDelta < 0) {
			mouseState[AstrumMouseButtonType_ScrollDown] = true;
		}
	}
}

void AstrumRawInputSingleton::Dispose() {
	RAWINPUTDEVICE rid{};
	rid.usUsagePage = 0x01; // Generic Desktop Controls
	rid.usUsage = 0x06;     // Keyboard
	rid.dwFlags = RIDEV_REMOVE;
	rid.hwndTarget = nullptr;
	RegisterRawInputDevices(&rid, 1, sizeof(rid));

	rid.usUsage = 0x02; // Mouse
	RegisterRawInputDevices(&rid, 1, sizeof(rid));
}

void AstrumRawInputSingleton::UpdateMousePosition() {
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(AstrumWindow::GetHandle(), &point);

	auto resolution = AstrumRenderer::Instance().GetResolution();
	auto rsrate = AstrumRenderer::Instance().GetRSRate();
	AstrumDoubleVector2 newMousePos{
		point.x * rsrate.X,
		point.y * rsrate.Y
	};
	newMousePos.Y = resolution.Height - newMousePos.Y;
	// Raw Input의 상대 이동량이 아닌, 절대 좌표 기반의 이동량 계산
	// mouseMovement = newMousePos - mousePosition; 
	mousePosition = newMousePos;
}
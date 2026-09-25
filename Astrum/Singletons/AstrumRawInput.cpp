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
		AstrumException(__LINE__, __FILE__, std::format("Failed to register raw input device. Error code: {}", GetLastError())).Alert();
		return;
	}
}

void AstrumRawInputSingleton::Update() {
	UpdateMousePosition();
}

void AstrumRawInputSingleton::Clear() {
	//이전 상태 갱신 및 보존
	memcpy(previousKeyState, keyState, sizeof(keyState));
	memcpy(previousMouseState, mouseState, sizeof(mouseState));
	// 상태 초기화
	// 휠은 '눌림'이 한 프레임만 유지되는 입력이므로, 게임 로직이 이번 프레임에 확인한 뒤(프레임 끝)에 초기화합니다.
	// (프레임 시작 시점에 초기화하면 프레임 사이에 들어온 휠 입력이 게임 로직에 전달되기 전에 지워집니다.)
	mouseState[AstrumMouseButtonType_ScrollUp] = false;
	mouseState[AstrumMouseButtonType_ScrollDown] = false;
	mouseMovement = { 0, 0 };
	wheelMovement = 0;
	keyQueue.clear();
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
	mouseMovement.X += mouse.lLastX;
	mouseMovement.Y += mouse.lLastY;

	// 버튼 상태 갱신
	if (mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN) mouseState[AstrumMouseButtonType_Left] = true;
	if (mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP) mouseState[AstrumMouseButtonType_Left] = false;
	if (mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN) mouseState[AstrumMouseButtonType_Right] = true;
	if (mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP) mouseState[AstrumMouseButtonType_Right] = false;
	if (mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN) mouseState[AstrumMouseButtonType_Center] = true;
	if (mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP) mouseState[AstrumMouseButtonType_Center] = false;

	// 마우스 휠 처리
	if (mouse.usButtonFlags & RI_MOUSE_WHEEL) {
		const short wheelDelta = static_cast<short>(mouse.usButtonData);
		if (wheelDelta > 0) {
			mouseState[AstrumMouseButtonType_ScrollUp] = true;
		}
		else if (wheelDelta < 0) {
			mouseState[AstrumMouseButtonType_ScrollDown] = true;
		}
		wheelMovement += wheelDelta; // 휠 누적
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

	// 클라이언트 좌표를 논리 해상도 좌표(왼쪽 아래 원점)로 변환합니다. (창 크기 변경에 따른 확대/축소와 레터박스 여백 반영)
	mousePosition = AstrumRenderer::Instance().ClientToResolution(
		static_cast<double>(point.x),
		static_cast<double>(point.y)
	);
}
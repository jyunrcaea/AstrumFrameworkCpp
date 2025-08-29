#include "AstrumRawInput.hpp"
#include <string>
#include <format>
#include <windows.h>
#include "AstrumWindow.hpp"
#include "AstrumChrono.hpp"

void AstrumRawInputSingleton::Initialize() {
	RAWINPUTDEVICE rid{};
	rid.usUsagePage = 0x01; // Generic Desktop Controls
	rid.usUsage = 0x06;     // Keyboard
	rid.dwFlags = 0;
	rid.hwndTarget = AstrumWindow::GetHandle();
	if (false == RegisterRawInputDevices(&rid, 1, sizeof(rid))) {
		throw AstrumException(std::format("Failed to register raw input device. Error code: {}", GetLastError()));
	}
}

void AstrumRawInputSingleton::Update(const RAWKEYBOARD& kb) {
	inputQueue.emplace_back(
		kb.MakeCode,
		false == (kb.Flags & RI_KEY_BREAK),
		AstrumChrono::GetRunningTime()
	);
}

void AstrumRawInputSingleton::Dispose() {
	RAWINPUTDEVICE rid{};
	rid.usUsagePage = 0x01; // Generic Desktop Controls
	rid.usUsage = 0x06;     // Keyboard
	rid.dwFlags = RIDEV_REMOVE;
	rid.hwndTarget = nullptr;
	if (false == RegisterRawInputDevices(&rid, 1, sizeof(rid))) {
#if _DEBUG
		throw AstrumException(std::format("Failed to unregister raw input device. Error code: {}", GetLastError()));
#endif
	}
}
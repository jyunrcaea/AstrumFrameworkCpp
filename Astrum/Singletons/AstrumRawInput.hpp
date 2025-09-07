#pragma once
#include <vector>
#include <windows.h>
#include "AstrumSingleton.hpp"
#include "../Data/AstrumRawInputKeyData.hpp"
#include "../Enums/AstrumMouseButtonType.hpp"
#include "../Vectors/AstrumLongVector2.hpp"
#include "../Vectors/AstrumDoubleVector2.hpp"

class AstrumRawInputSingleton : public AstrumSingleton<AstrumRawInputSingleton>
{
	friend class AstrumSingleton<AstrumRawInputSingleton>;
	friend class AstrumRawInput;

private:
	void Initialize();
	void Update();
	void Enqueue(const RAWINPUT& raw);
	void EnqueueKeyboard(const RAWKEYBOARD& kb);
	void EnqueueMouse(const RAWMOUSE& mouse);
	void Clear();
	void Dispose();

public:
	const std::vector<AstrumRawInputKeyData>& GetKeyboardQueue() const { return keyQueue; }

public:
	bool IsKeyPressed(uint8_t vk) const { return keyState[vk]; }
	bool IsKeyReleased(uint8_t vk) const { return keyState[vk]; }
	bool WasKeyPressed(uint8_t vk) const { return false == previousKeyState[vk] && keyState[vk]; }
	bool WasKeyReleased(uint8_t vk) const { return previousKeyState[vk] && false == keyState[vk]; }

	AstrumDoubleVector2 GetMousePosition() const { return mousePosition; }
	AstrumLongVector2 GetMouseMovement() const { return mouseMovement; }
	bool IsMousePressed(AstrumMouseButtonType button) const { return mouseState[button]; }
	bool BeforeMousePressed(AstrumMouseButtonType button) const { return previousMouseState[button]; }
	bool WasMouseReleased(AstrumMouseButtonType button) const { return previousMouseState[button] && false == mouseState[button]; }

	double GetMouseWheelMovement() const { return wheelMovement / 120.0; }

private:
	// 마우스 절대 좌표 갱신
	void UpdateMousePosition();

	bool keyState[256]{ false, };
	bool previousKeyState[256]{ false, };

	bool mouseState[AstrumMouseButtonType_Count]{};
	bool previousMouseState[AstrumMouseButtonType_Count]{};

	int wheelMovement = 0;

	AstrumLongVector2 mouseMovement{};
	AstrumDoubleVector2 mousePosition{};

private:
	std::vector<AstrumRawInputKeyData> keyQueue;
	//std::vector<AstrumRawInputKeyInformation> mouseQueue;
};

class AstrumRawInput {
private:
	friend class AstrumWindowSingleton;

	static void Initialize() { AstrumRawInputSingleton::Instance().Initialize(); }
	static void Enqueue(const RAWINPUT& raw) { AstrumRawInputSingleton::Instance().Enqueue(raw); }
	static void Dispose() { AstrumRawInputSingleton::Instance().Dispose(); }

private:
	friend class AstrumFrameworkSingleton;

	static void Clear() { AstrumRawInputSingleton::Instance().Clear(); }
	static void Update() { AstrumRawInputSingleton::Instance().Update(); }

public:
	// 이전 업데이트 이후 쌓이게 된 입력들을 가져옵니다.
	static const std::vector<AstrumRawInputKeyData>& GetKeyboardQueue() { return AstrumRawInputSingleton::Instance().GetKeyboardQueue(); }
	//static const std::vector<AstrumRawInputKeyInformation>& GetMouseQueue() { return AstrumRawInputSingleton::Instance().GetQueue(); }

	static bool IsKeyPressed(uint8_t vk) { return AstrumRawInputSingleton::Instance().IsKeyPressed(vk); }
	static bool IsKeyReleased(uint8_t vk) { return AstrumRawInputSingleton::Instance().IsKeyReleased(vk); }
	static bool WasKeyPressed(uint8_t vk) { return AstrumRawInputSingleton::Instance().WasKeyPressed(vk); }
	static bool WasKeyReleased(uint8_t vk) { return AstrumRawInputSingleton::Instance().WasKeyReleased(vk); }

	static AstrumDoubleVector2 GetMousePosition() { return AstrumRawInputSingleton::Instance().GetMousePosition(); }
	static AstrumLongVector2 GetMouseMovement() { return AstrumRawInputSingleton::Instance().GetMouseMovement(); }
	static bool IsMousePressed(AstrumMouseButtonType button = AstrumMouseButtonType_Left) { return AstrumRawInputSingleton::Instance().IsMousePressed(button); }
	static bool BeforeMousePressed(AstrumMouseButtonType button = AstrumMouseButtonType_Left) { return AstrumRawInputSingleton::Instance().BeforeMousePressed(button); }
	static bool WasMouseReleased(AstrumMouseButtonType button = AstrumMouseButtonType_Left) { return AstrumRawInputSingleton::Instance().WasMouseReleased(button); }

	// 해당 키가 그전까지 눌려있지 않다가 지금 눌린 상태인지 (즉, 이번 프레임에 눌린 상태인지)
	static bool IsMouseClickNow(AstrumMouseButtonType button = AstrumMouseButtonType_Left) { return IsMousePressed(button) && false == BeforeMousePressed(button); }

	static double GetMouseWheelMovement() { return AstrumRawInputSingleton::Instance().GetMouseWheelMovement(); }
};
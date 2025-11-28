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
	/// <summary>
	/// 키보드 입력 큐를 반환합니다.
	/// </summary>
	/// <returns>이전 업데이트 이후 발생한 키 입력 데이터의 벡터입니다.</returns>
	const std::vector<AstrumRawInputKeyData>& GetKeyboardQueue() const { return keyQueue; }

public:
	/// <summary>
	/// 특정 키가 현재 눌려있는지 확인합니다.
	/// </summary>
	/// <param name="vk">확인할 가상 키 코드입니다.</param>
	/// <returns>키가 눌려있으면 true, 아니면 false를 반환합니다.</returns>
	bool IsKeyPressed(uint8_t vk) const { return keyState[vk]; }
	/// <summary>
	/// 특정 키가 현재 놓여있는지 확인합니다.
	/// </summary>
	/// <param name="vk">확인할 가상 키 코드입니다.</param>
	/// <returns>키가 놓여있으면 true, 아니면 false를 반환합니다.</returns>
	bool IsKeyReleased(uint8_t vk) const { return keyState[vk]; }
	/// <summary>
	/// 특정 키가 이번 프레임에 눌렸는지 확인합니다.
	/// </summary>
	/// <param name="vk">확인할 가상 키 코드입니다.</param>
	/// <returns>이전 프레임에는 놓여있었고 현재 프레임에 눌렸으면 true를 반환합니다.</returns>
	bool WasKeyPressed(uint8_t vk) const { return false == previousKeyState[vk] && keyState[vk]; }
	/// <summary>
	/// 특정 키가 이번 프레임에 놓였는지 확인합니다.
	/// </summary>
	/// <param name="vk">확인할 가상 키 코드입니다.</param>
	/// <returns>이전 프레임에는 눌려있었고 현재 프레임에 놓였으면 true를 반환합니다.</returns>
	bool WasKeyReleased(uint8_t vk) const { return previousKeyState[vk] && false == keyState[vk]; }

	/// <summary>
	/// 마우스의 절대 위치를 반환합니다.
	/// </summary>
	/// <returns>렌더 해상도 기준의 마우스 좌표입니다.</returns>
	AstrumDoubleVector2 GetMousePosition() const { return mousePosition; }
	/// <summary>
	/// 마우스의 상대 이동량을 반환합니다.
	/// </summary>
	/// <returns>마지막 프레임 이후 마우스의 상대 이동량입니다.</returns>
	AstrumLongVector2 GetMouseMovement() const { return mouseMovement; }
	/// <summary>
	/// 특정 마우스 버튼이 현재 눌려있는지 확인합니다.
	/// </summary>
	/// <param name="button">확인할 마우스 버튼입니다.</param>
	/// <returns>버튼이 눌려있으면 true, 아니면 false를 반환합니다.</returns>
	bool IsMousePressed(AstrumMouseButtonType button) const { return mouseState[button]; }
	/// <summary>
	/// 특정 마우스 버튼이 이전 프레임에 눌려있었는지 확인합니다.
	/// </summary>
	/// <param name="button">확인할 마우스 버튼입니다.</param>
	/// <returns>이전 프레임에 눌려있었으면 true, 아니면 false를 반환합니다.</returns>
	bool BeforeMousePressed(AstrumMouseButtonType button) const { return previousMouseState[button]; }
	/// <summary>
	/// 특정 마우스 버튼이 이번 프레임에 놓였는지 확인합니다.
	/// </summary>
	/// <param name="button">확인할 마우스 버튼입니다.</param>
	/// <returns>이전 프레임에는 눌려있었고 현재 프레임에 놓였으면 true를 반환합니다.</returns>
	bool WasMouseReleased(AstrumMouseButtonType button) const { return previousMouseState[button] && false == mouseState[button]; }

	/// <summary>
	/// 마우스 휠의 회전량을 반환합니다.
	/// </summary>
	/// <returns>마우스 휠의 회전량입니다. 양수는 위로, 음수는 아래로입니다.</returns>
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
	/// <summary>
	/// 이전 업데이트 이후 발생한 키보드 입력 이벤트들을 반환합니다.
	/// </summary>
	/// <returns>축적된 키 입력 데이터의 벡터입니다.</returns>
	static const std::vector<AstrumRawInputKeyData>& GetKeyboardQueue() { return AstrumRawInputSingleton::Instance().GetKeyboardQueue(); }
	//static const std::vector<AstrumRawInputKeyInformation>& GetMouseQueue() { return AstrumRawInputSingleton::Instance().GetQueue(); }

	/// <summary>
	/// 특정 키가 현재 눌려있는지 확인합니다.
	/// </summary>
	/// <param name="vk">확인할 가상 키 코드입니다.</param>
	/// <returns>키가 눌려있으면 true, 아니면 false를 반환합니다.</returns>
	static bool IsKeyPressed(uint8_t vk) { return AstrumRawInputSingleton::Instance().IsKeyPressed(vk); }
	/// <summary>
	/// 특정 키가 현재 놓여있는지 확인합니다.
	/// </summary>
	/// <param name="vk">확인할 가상 키 코드입니다.</param>
	/// <returns>키가 놓여있으면 true, 아니면 false를 반환합니다.</returns>
	static bool IsKeyReleased(uint8_t vk) { return AstrumRawInputSingleton::Instance().IsKeyReleased(vk); }
	/// <summary>
	/// 특정 키가 이번 프레임에 눌렸는지 확인합니다.
	/// </summary>
	/// <param name="vk">확인할 가상 키 코드입니다.</param>
	/// <returns>이전 프레임에는 놓여있었고 현재 프레임에 눌렸으면 true를 반환합니다.</returns>
	static bool WasKeyPressed(uint8_t vk) { return AstrumRawInputSingleton::Instance().WasKeyPressed(vk); }
	/// <summary>
	/// 특정 키가 이번 프레임에 놓였는지 확인합니다.
	/// </summary>
	/// <param name="vk">확인할 가상 키 코드입니다.</param>
	/// <returns>이전 프레임에는 눌려있었고 현재 프레임에 놓였으면 true를 반환합니다.</returns>
	static bool WasKeyReleased(uint8_t vk) { return AstrumRawInputSingleton::Instance().WasKeyReleased(vk); }

	/// <summary>
	/// 마우스의 절대 위치를 반환합니다.
	/// </summary>
	/// <returns>렌더 해상도 기준의 마우스 좌표입니다.</returns>
	static AstrumDoubleVector2 GetMousePosition() { return AstrumRawInputSingleton::Instance().GetMousePosition(); }
	/// <summary>
	/// 마우스의 상대 이동량을 반환합니다.
	/// </summary>
	/// <returns>마지막 프레임 이후 마우스의 상대 이동량입니다.</returns>
	static AstrumLongVector2 GetMouseMovement() { return AstrumRawInputSingleton::Instance().GetMouseMovement(); }
	/// <summary>
	/// 특정 마우스 버튼이 현재 눌려있는지 확인합니다. 기본값은 좌측 버튼입니다.
	/// </summary>
	/// <param name="button">확인할 마우스 버튼입니다. 기본값은 AstrumMouseButtonType_Left입니다.</param>
	/// <returns>버튼이 눌려있으면 true, 아니면 false를 반환합니다.</returns>
	static bool IsMousePressed(AstrumMouseButtonType button = AstrumMouseButtonType_Left) { return AstrumRawInputSingleton::Instance().IsMousePressed(button); }
	/// <summary>
	/// 특정 마우스 버튼이 이전 프레임에 눌려있었는지 확인합니다. 기본값은 좌측 버튼입니다.
	/// </summary>
	/// <param name="button">확인할 마우스 버튼입니다. 기본값은 AstrumMouseButtonType_Left입니다.</param>
	/// <returns>이전 프레임에 눌려있었으면 true, 아니면 false를 반환합니다.</returns>
	static bool BeforeMousePressed(AstrumMouseButtonType button = AstrumMouseButtonType_Left) { return AstrumRawInputSingleton::Instance().BeforeMousePressed(button); }
	/// <summary>
	/// 특정 마우스 버튼이 이번 프레임에 놓였는지 확인합니다. 기본값은 좌측 버튼입니다.
	/// </summary>
	/// <param name="button">확인할 마우스 버튼입니다. 기본값은 AstrumMouseButtonType_Left입니다.</param>
	/// <returns>이전 프레임에는 눌려있었고 현재 프레임에 놓였으면 true를 반환합니다.</returns>
	static bool WasMouseReleased(AstrumMouseButtonType button = AstrumMouseButtonType_Left) { return AstrumRawInputSingleton::Instance().WasMouseReleased(button); }

	/// <summary>
	/// 특정 마우스 버튼이 이번 프레임에 클릭되었는지 확인합니다. 기본값은 좌측 버튼입니다.
	/// </summary>
	/// <param name="button">확인할 마우스 버튼입니다. 기본값은 AstrumMouseButtonType_Left입니다.</param>
	/// <returns>이전 프레임에는 눌려있지 않았고 현재 프레임에 눌렸으면 true를 반환합니다.</returns>
	static bool IsMouseClickNow(AstrumMouseButtonType button = AstrumMouseButtonType_Left) { return IsMousePressed(button) && false == BeforeMousePressed(button); }

	/// <summary>
	/// 마우스 휠의 회전량을 반환합니다.
	/// </summary>
	/// <returns>마우스 휠의 회전량입니다. 양수는 위로, 음수는 아래로입니다.</returns>
	static double GetMouseWheelMovement() { return AstrumRawInputSingleton::Instance().GetMouseWheelMovement(); }
};
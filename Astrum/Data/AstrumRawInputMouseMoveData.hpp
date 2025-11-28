#pragma once
#include "../Enums/AstrumMouseButtonType.hpp"

/// <summary>
/// 마우스 이동 입력 데이터를 포함하는 구조체입니다.
/// </summary>
struct AstrumRawInputMouseData
{
	/// <summary>
	/// 마우스의 X축 상대 이동량입니다.
	/// </summary>
	float moveX;
	/// <summary>
	/// 마우스의 Y축 상대 이동량입니다.
	/// </summary>
	float moveY;
	/// <summary>
	/// 마우스 입력이 발생한 시간(초)입니다.
	/// </summary>
	double Timestamp;
};
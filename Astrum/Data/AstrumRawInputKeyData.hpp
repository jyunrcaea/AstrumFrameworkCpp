#pragma once
/// <summary>
/// 키보드 입력 데이터를 포함하는 구조체입니다.
/// </summary>
struct AstrumRawInputKeyData
{
	/// <summary>
	/// 키의 가상 키 코드(Virtual Key Code)입니다.
	/// </summary>
	unsigned short VirtualKey;
	/// <summary>
	/// 키의 스캔 코드(Scan Code)입니다.
	/// </summary>
	unsigned short ScanCode;
	/// <summary>
	/// 키의 입력 상태입니다. true이면 눌림, false이면 놓임입니다.
	/// </summary>
	bool IsPressed;
	/// <summary>
	/// 입력이 발생한 시간(초)입니다.
	/// </summary>
	double Timestamp;
};
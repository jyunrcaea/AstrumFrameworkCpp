#pragma once
#include "../Enums/AstrumMaterialFlipType.hpp"
#include "../Vectors/AstrumVector4.hpp"
#include "../Graphics/AstrumTextureSampler.hpp"

/// <summary>
/// 재질(머터리얼)의 속성을 포함하는 구조체입니다.
/// Direct3D 상수 버퍼에 사용됩니다.
/// </summary>
struct AstrumMaterialData
{
	/// <summary>
	/// 재질의 기본 색상입니다. RGBA 형식으로 각 값은 0~1 범위입니다.
	/// 기본값은 (1, 1, 1, 1)인 흰색입니다.
	/// </summary>
	AstrumVector4 BaseColor = { 1,1,1,1 };
	/// <summary>
	/// 재질의 불투명도입니다. 0~1 범위로 0은 완전 투명, 1은 완전 불투명입니다.
	/// 기본값은 1입니다.
	/// </summary>
	float Opacity = 1;
	/// <summary>
	/// 텍스처의 너비(픽셀)입니다. 기본값은 0입니다.
	/// </summary>
	int Width = 0;
	/// <summary>
	/// 텍스처의 높이(픽셀)입니다. 기본값은 0입니다.
	/// </summary>
	int Height = 0;
	/// <summary>
	/// 텍스처의 뒤집기 옵션입니다. 기본값은 AstrumMaterialFlipType_None입니다.
	/// </summary>
	AstrumMaterialFlipType Flip = AstrumMaterialFlipType_None;
};
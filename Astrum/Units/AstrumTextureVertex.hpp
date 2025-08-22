#pragma once
#include "../Vectors/AstrumVector3.hpp"
#include "../Vectors/AstrumVector2.hpp"

namespace Astrum
{
	// 텍스처 렌더링을 위한 정점 구조체
	struct TextureVertex {
		Vector3 Position; // 정점 위치
		Vector2 UV;       // 텍스처 좌표 (TexCoord)
	};
}
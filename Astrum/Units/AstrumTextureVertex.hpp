#pragma once
#include "../Vectors/AstrumVector3.hpp"
#include "../Vectors/AstrumVector2.hpp"

// 텍스처 렌더링을 위한 정점 구조체
struct AstrumTextureVertex {
    AstrumVector3 Position; // 정점 위치
    AstrumVector2 UV;       // 텍스처 좌표 (TexCoord)
};
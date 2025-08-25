#pragma once
#include "../Vectors/AstrumVector4.hpp"
#include "../Graphics/AstrumTextureSampler.hpp"

enum AstrumMaterialFlipType {
	AstrumMaterialFlipType_None = 0,
	AstrumMaterialFlipType_X = 1,
	AstrumMaterialFlipType_Y = 2,
	AstrumMaterialFlipType_XY = 3
};

struct AstrumMaterialData
{
	AstrumVector4 BaseColor = { 1,1,1,1 };
	float Opacity = 1;
	int Width = 0;
	int Height = 0;
	AstrumMaterialFlipType Flip = AstrumMaterialFlipType_None;
};
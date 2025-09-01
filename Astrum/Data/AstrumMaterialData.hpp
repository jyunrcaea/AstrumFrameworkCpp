#pragma once
#include "../Enums/AstrumMaterialFlipType.hpp"
#include "../Vectors/AstrumVector4.hpp"
#include "../Graphics/AstrumTextureSampler.hpp"

struct AstrumMaterialData
{
	AstrumVector4 BaseColor = { 1,1,1,1 };
	float Opacity = 1;
	int Width = 0;
	int Height = 0;
	AstrumMaterialFlipType Flip = AstrumMaterialFlipType_None;
};
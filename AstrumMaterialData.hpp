#pragma once
#include "AstrumVector4.hpp"
#include "AstrumTextureSampler.hpp"

struct AstrumMaterialData
{
	AstrumVector4 BaseColor = { 1,1,1,1 };
	float Opacity = 1;
	int Width = 0;
	int Height = 0;
	AstrumTextureSampleType sampleType = AstrumTextureSampleType::AstrumTextureSampleType_Linear;
};
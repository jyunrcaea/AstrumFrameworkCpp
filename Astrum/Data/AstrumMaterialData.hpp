#pragma once
#include "../Vectors/AstrumVector4.hpp"
#include "../Graphics/AstrumTextureSampler.hpp"

namespace Astrum
{
	enum MaterialFlipType {
		MaterialFlipType_None = 0,
		MaterialFlipType_X = 1,
		MaterialFlipType_Y = 2,
		MaterialFlipType_XY = 3
	};

	struct MaterialData
	{
		Vector4 BaseColor = { 1,1,1,1 };
		float Opacity = 1;
		int Width = 0;
		int Height = 0;
		MaterialFlipType Flip = MaterialFlipType_None;
	};
}
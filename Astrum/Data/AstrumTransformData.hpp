#pragma once
#include "../Units/AstrumMatrix.hpp"

namespace Astrum
{
	struct alignas(16) TransformData {
		Matrix World;
		Matrix View;
		Matrix Projection;
		Matrix WorldView;
		Matrix WorldViewProjection;
	};
}
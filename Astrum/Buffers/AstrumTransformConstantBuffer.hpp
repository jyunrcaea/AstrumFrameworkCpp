#pragma once
#include <span>
#include <cstddef>
#include "AstrumConstantBuffer.hpp"
#include "../Data/AstrumTransformData.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

namespace Astrum {
	class TransformConstantBuffer : public ConstantBuffer {
	public:
		TransformConstantBuffer();

		Matrix& World = data.World;
		Matrix& View = data.View;
		Matrix& Projection = data.Projection;
		Matrix& WorldView = data.WorldView;
		Matrix& WorldViewProjection = data.WorldViewProjection;

		virtual void UpdateBuffer() override;

	private:
		TransformData data{};
	};
}
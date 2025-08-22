#pragma once
#include <memory>
#include <d3d11.h>

namespace Astrum {
	struct IConstantBuffer {
		virtual ~IConstantBuffer() = default;
		virtual ID3D11Buffer* GetConstantBuffer() const = 0;
		virtual void UpdateBuffer() = 0;
	};
}
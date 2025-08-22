#include "AstrumTransformConstantBuffer.hpp"

namespace Astrum {
	TransformConstantBuffer::TransformConstantBuffer()
		: ConstantBuffer(sizeof(TransformData)) {
	#if _DEBUG
		if (GetBufferSize() % 16 != 0)
			throw Exception("Constant buffer size must be 16-byte aligned.");
	#endif
		data.View = Matrix::Identity;
	}

	void TransformConstantBuffer::UpdateBuffer() {
		WorldView = World * View;
		WorldViewProjection = WorldView * Projection;

		World.Transpose();
		View.Transpose();
		Projection.Transpose();
		WorldView.Transpose();
		WorldViewProjection.Transpose();

		//Update(std::as_bytes(std::span{ &data, 1 }));
		UpdateConstantBuffer(data);
		SetVertexShaderConstantBuffer(0);
	#if _DEBUG
		if (nullptr == buffer) throw Exception("Buffer be nullptr.");
	#endif
	}
}
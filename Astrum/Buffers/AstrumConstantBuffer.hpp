#pragma once
#include <wrl/client.h>
#include <vector>
#include <span>
#include <cstdint>
#include <cstring>
#include "IAstrumConstantBuffer.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

namespace Astrum {
	class ConstantBuffer : public IConstantBuffer {
	public:
		// constructor is not apply polymorphism.
		 ConstantBuffer(unsigned int size);
		virtual ~ConstantBuffer() override;
		virtual void Dispose();
		ID3D11Buffer* GetConstantBuffer() const override;
		unsigned int GetBufferSize() const;

		virtual void UpdateBuffer() override = 0;

		template<typename T>
		void UpdateConstantBuffer(T& data);
		void SetPixelShaderConstantBuffer(unsigned int slot);
		void SetVertexShaderConstantBuffer(unsigned int slot);
		void SetGeometryShaderConstantBuffer(unsigned int slot);
		void SetHullShaderConstantBuffer(unsigned int slot);
		void SetDomainShaderConstantBuffer(unsigned int slot);
		void SetComputeShaderConstantBuffer(unsigned int slot);

	protected:
		void Update(std::span<const std::byte> data);
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		const unsigned int bufferSize;
	};

	template<typename T>
	inline void ConstantBuffer::UpdateConstantBuffer(T& data) {
		Update(std::as_bytes(std::span{ &data, 1 }));
	}
}
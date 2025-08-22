#include "AstrumConstantBuffer.hpp"

namespace Astrum {
	ConstantBuffer::ConstantBuffer(unsigned int size) : bufferSize(size)
	{
		D3D11_BUFFER_DESC desc = {};
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = size;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		if (FAILED(Renderer::Instance().GetDevice()->CreateBuffer(&desc, nullptr, buffer.GetAddressOf())))
			throw Exception("Failed to create constant buffer.");
	}

	ConstantBuffer::~ConstantBuffer() {
		Dispose();
	}

	void ConstantBuffer::Dispose() {
		if (buffer) {
			buffer.Reset();
		}
	}

	unsigned int ConstantBuffer::GetBufferSize() const { return bufferSize; }

	ID3D11Buffer* ConstantBuffer::GetConstantBuffer() const {
		return buffer.Get();
	}

	void ConstantBuffer::Update(std::span<const std::byte> data) {
		auto* context = Renderer::Instance().GetContext();

		D3D11_MAPPED_SUBRESOURCE mapped{};
		if (FAILED(context->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped))) {
	#if _DEBUG
			throw Exception("Failed to map constant buffer.");
	#else
			std::cout << "[ERROR] Failed to map constant buffer." << std::endl;
	#endif
		}

		std::memcpy(mapped.pData, data.data(), bufferSize);
		context->Unmap(buffer.Get(), 0);
	}

	void ConstantBuffer::SetPixelShaderConstantBuffer(unsigned int slot) {
		Renderer::Instance().GetContext()->PSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
	}

	void ConstantBuffer::SetVertexShaderConstantBuffer(unsigned int slot) {
		Renderer::Instance().GetContext()->VSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
	}

	void ConstantBuffer::SetGeometryShaderConstantBuffer(unsigned int slot) {
		Renderer::Instance().GetContext()->GSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
	}

	void ConstantBuffer::SetHullShaderConstantBuffer(unsigned int slot) {
		Renderer::Instance().GetContext()->HSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
	}

	void ConstantBuffer::SetDomainShaderConstantBuffer(unsigned int slot) {
		Renderer::Instance().GetContext()->DSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
	}

	void ConstantBuffer::SetComputeShaderConstantBuffer(unsigned int slot) {
		Renderer::Instance().GetContext()->CSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
	}
}

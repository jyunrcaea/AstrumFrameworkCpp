#include "AstrumConstantBuffer.hpp"

AstrumConstantBuffer::AstrumConstantBuffer(unsigned int size) : bufferSize(size)
{
    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.ByteWidth = size;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    if (FAILED(AstrumRenderer::Instance().GetDevice()->CreateBuffer(&desc, nullptr, &buffer)))
        throw AstrumException("Failed to create constant buffer.");
}

AstrumConstantBuffer::~AstrumConstantBuffer() {
    Dispose();
}

void AstrumConstantBuffer::Dispose() {
    if (buffer) {
        buffer.Reset();
    }
}

ID3D11Buffer* AstrumConstantBuffer::GetConstantBuffer() const {
    return buffer.Get();
}

void AstrumConstantBuffer::Update(std::span<const std::byte> data) {
    auto* context = AstrumRenderer::Instance().GetContext();

    D3D11_MAPPED_SUBRESOURCE mapped{};
    if (FAILED(context->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped)))
        throw AstrumException("Failed to map constant buffer.");

    std::memcpy(mapped.pData, data.data(), bufferSize);
    context->Unmap(buffer.Get(), 0);
}
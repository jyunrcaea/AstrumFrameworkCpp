#pragma once
#include "IAstrumConstantBuffer.hpp"
#include "AstrumRenderer.hpp"
#include "AstrumException.hpp"

#include <wrl/client.h>
#include <vector>
#include <span>
#include <cstdint>
#include <cstring>

class AstrumConstantBuffer : public IAstrumConstantBuffer {
public:
    explicit AstrumConstantBuffer(uint32_t size)
        : size(size)
    {
        D3D11_BUFFER_DESC desc = {};
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.ByteWidth = size;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        if (FAILED(AstrumRenderer::Instance().GetDevice()->CreateBuffer(&desc, nullptr, &buffer)))
            throw AstrumException("Failed to create constant buffer.");
    }

    ~AstrumConstantBuffer() override {
        Dispose();
    }

    virtual void Dispose() {
        if (buffer) {
            buffer.Reset();
        }
    }

    ID3D11Buffer* GetConstantBuffer() const override {
        return buffer.Get();
    }

protected:
    void Update(std::span<const std::byte> data) {
        auto* context = AstrumRenderer::Instance().GetContext();

        D3D11_MAPPED_SUBRESOURCE mapped{};
        if (FAILED(context->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped)))
            throw AstrumException("Failed to map constant buffer.");

        std::memcpy(mapped.pData, data.data(), size);
        context->Unmap(buffer.Get(), 0);
    }

    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    uint32_t size;
};

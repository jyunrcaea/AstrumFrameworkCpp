#pragma once
#include <wrl/client.h>
#include <vector>
#include <span>
#include <cstdint>
#include <cstring>
#include "IAstrumConstantBuffer.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

class AstrumConstantBuffer : public IAstrumConstantBuffer {
public:
    // constructor is not apply polymorphism.
     AstrumConstantBuffer(unsigned int size);
    virtual ~AstrumConstantBuffer() override;
    virtual void Dispose();
    ID3D11Buffer* GetConstantBuffer() const override;

protected:
    void Update(std::span<const std::byte> data);

    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    const unsigned int bufferSize;
};
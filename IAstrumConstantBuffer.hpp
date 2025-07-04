#pragma once
#include <d3d11.h>

struct IAstrumConstantBuffer {
    virtual ~IAstrumConstantBuffer() = default;
    virtual ID3D11Buffer* GetConstantBuffer() const = 0;
};

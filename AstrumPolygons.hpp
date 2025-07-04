#pragma once

#include <bits/stdc++.h>
#include <d3d11.h>
#include <dxgi.h>
#include <wrl/client.h>
#include <cstdint>
#include "IAstrumRenderable.hpp"
#include "AstrumVertexColor.hpp"
#include "AstrumException.hpp"
#include "AstrumRenderer.hpp"


using Microsoft::WRL::ComPtr;

class AstrumPolygons : public IAstrumRenderable, public enable_shared_from_this<AstrumPolygons> {
public:
    AstrumPolygons(const std::vector<AstrumVertexColor>& vertices,
        const std::vector<uint16_t>& indices,
        D3D11_PRIMITIVE_TOPOLOGY primitive,
        DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN,
        D3D11_USAGE vertexUsage = D3D11_USAGE_DEFAULT,
        D3D11_USAGE indexUsage = D3D11_USAGE_DEFAULT);
    virtual ~AstrumPolygons() override;
    virtual void Render() override;
    void Dispose();

protected:
    virtual void Rendering() override { };

private:
    D3D11_PRIMITIVE_TOPOLOGY    primitive;
    ComPtr<ID3D11Buffer>        vertexBuffer;
    ComPtr<ID3D11Buffer>        indexBuffer;
    DXGI_FORMAT                  indexBufferFormat;
    UINT                         indexCount = 0;
};
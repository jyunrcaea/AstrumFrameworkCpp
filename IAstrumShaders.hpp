#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>

struct IAstrumShader {
    virtual ~IAstrumShader() = default;
    virtual ID3DBlob* GetShaderBlob() const = 0;
};

struct IAstrumVertexShader {
    virtual ~IAstrumVertexShader() = default;
    virtual ID3D11VertexShader* GetVertexShader() const = 0;
};

struct IAstrumPixelShader {
    virtual ~IAstrumPixelShader() = default;
    virtual ID3D11PixelShader* GetPixelShader() const = 0;
};

struct IAstrumHullShader {
    virtual ~IAstrumHullShader() = default;
    virtual ID3D11HullShader* GetHullShader() const = 0;
};

struct IAstrumGeometryShader {
    virtual ~IAstrumGeometryShader() = default;
    virtual ID3D11GeometryShader* GetGeometryShader() const = 0;
};

struct IAstrumDomainShader {
    virtual ~IAstrumDomainShader() = default;
    virtual ID3D11DomainShader* GetDomainShader() const = 0;
};

struct IAstrumConfigurableShader {
    virtual ~IAstrumConfigurableShader() = default;
    virtual void SetShader() = 0;
};
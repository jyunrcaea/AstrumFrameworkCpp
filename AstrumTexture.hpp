#pragma once
#include <d3d11_1.h>
#include <string>
#include "AstrumImage.hpp"
#include "AstrumRenderer.hpp"
#include "AstrumException.hpp"

class AstrumTexture
{
private:
    AstrumTexture(const AstrumTexture&) = delete;
    AstrumTexture& operator=(const AstrumTexture&) = delete;
public:
    AstrumTexture(const AstrumImage& image);
    ~AstrumTexture();

    ID3D11ShaderResourceView* GetShaderResourceView() const;
private:
    ID3D11ShaderResourceView* shaderResourceView = nullptr;
};
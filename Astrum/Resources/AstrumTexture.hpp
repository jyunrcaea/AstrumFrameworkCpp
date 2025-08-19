#pragma once
#include <d3d11_1.h>
#include <string>
#include "AstrumImage.hpp"
#include "../Singletons/AstrumRenderer.hpp"

class AstrumTexture
{
private:
    AstrumTexture(const AstrumTexture&) = delete;
    AstrumTexture& operator=(const AstrumTexture&) = delete;
public:
    AstrumTexture(const std::wstring& path);
    AstrumTexture(const AstrumImage& image);
    ~AstrumTexture();

    ID3D11ShaderResourceView* GetShaderResourceView() const;
    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
private:
    ID3D11ShaderResourceView* shaderResourceView = nullptr;
    unsigned int width = 0, height = 0;

public:
    static std::shared_ptr<AstrumTexture> MakeShared(const std::wstring& path) { return std::make_shared<AstrumTexture>(path); }
    static std::shared_ptr<AstrumTexture> MakeShared(const AstrumImage& image) { return std::make_shared<AstrumTexture>(image); }
};
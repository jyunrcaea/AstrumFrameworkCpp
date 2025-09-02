#pragma once
#include <d3d11_1.h>
#include <wrl/client.h>
#include <string>
#include "AstrumImage.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "IAstrumTexture.hpp"

using Microsoft::WRL::ComPtr;

class AstrumTexture : public IAstrumTexture
{
private:
    AstrumTexture(const AstrumTexture&) = delete;
    AstrumTexture& operator=(const AstrumTexture&) = delete;

public:
    AstrumTexture(const std::filesystem::path& path);
    AstrumTexture(std::filesystem::path&& path);
    AstrumTexture(const AstrumImage& image);

    virtual ID3D11ShaderResourceView* GetShaderResourceView() const override;
    virtual unsigned int GetWidth() const override;
    virtual unsigned int GetHeight() const override;
private:
    ComPtr<ID3D11ShaderResourceView> shaderResourceView;
    unsigned int width = 0, height = 0;

public:
    static std::shared_ptr<AstrumTexture> MakeShared(const std::filesystem::path& path) { return std::make_shared<AstrumTexture>(path); }
    static std::shared_ptr<AstrumTexture> MakeShared(std::filesystem::path&& path) { return std::make_shared<AstrumTexture>(std::move(path)); }
    static std::shared_ptr<AstrumTexture> MakeShared(const AstrumImage& image) { return std::make_shared<AstrumTexture>(image); }
};
#include "AstrumTexture.hpp"
#include "../AstrumException.hpp"

AstrumTexture::AstrumTexture(const std::filesystem::path& path)
    : AstrumTexture(AstrumImage::MakeShared(path)) { }

AstrumTexture::AstrumTexture(std::filesystem::path&& path)
    : AstrumTexture(AstrumImage::MakeShared(std::move(path))) {}

AstrumTexture::AstrumTexture(std::shared_ptr<AstrumImage>&& image)
    : sourceImage(std::move(image))
{
    if (nullptr == sourceImage) AstrumException(__LINE__, __FILE__, "Failed to load texture. Because image is nullptr.").Alert();
    if (FAILED(DirectX::CreateShaderResourceView(
        AstrumRenderer::Instance().GetDevice(),
        sourceImage->GetImages(),
        sourceImage->GetImageCount(),
        sourceImage->GetMetadata(),
        shaderResourceView.GetAddressOf()
    ))) AstrumException(__LINE__, __FILE__, "Failed to create shader resource view for texture. (HRESULT: {})").Alert();

    width = static_cast<unsigned short>(sourceImage->GetImages()[0].width);
    height = static_cast<unsigned short>(sourceImage->GetImages()[0].height);
}

AstrumTexture::AstrumTexture(const std::shared_ptr<AstrumImage>& image)
    : sourceImage(image)
{
    if (nullptr == sourceImage) AstrumException(__LINE__, __FILE__, "Failed to load texture. Because image is nullptr.").Alert();
    if (FAILED(DirectX::CreateShaderResourceView(
        AstrumRenderer::Instance().GetDevice(),
        sourceImage->GetImages(),
        sourceImage->GetImageCount(),
        sourceImage->GetMetadata(),
        shaderResourceView.GetAddressOf()
    ))) AstrumException(__LINE__, __FILE__, "Failed to create shader resource view for texture. (HRESULT: {})").Alert();

    width = static_cast<unsigned short>(sourceImage->GetImages()[0].width);
    height = static_cast<unsigned short>(sourceImage->GetImages()[0].height);
}

ID3D11ShaderResourceView* AstrumTexture::GetShaderResourceView() const { return shaderResourceView.Get(); }
unsigned int AstrumTexture::GetWidth() const { return width; }
unsigned int AstrumTexture::GetHeight() const { return height; }
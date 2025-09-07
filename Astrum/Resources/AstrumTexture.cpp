#include "AstrumTexture.hpp"
#include "../AstrumException.hpp"

AstrumTexture::AstrumTexture(const std::filesystem::path& path)
    : AstrumTexture(AstrumImage(path)) { }

AstrumTexture::AstrumTexture(std::filesystem::path&& path)
    : AstrumTexture(AstrumImage(std::move(path))) {}

AstrumTexture::AstrumTexture(AstrumImage&& moveableImage)
{
	const AstrumImage image = std::move(moveableImage);

    if (FAILED(DirectX::CreateShaderResourceView(
        AstrumRenderer::Instance().GetDevice(),
        image.GetImages(),
        image.GetImageCount(),
        image.GetMetadata(),
        shaderResourceView.GetAddressOf()
    ))) throw AstrumException(__LINE__, __FILE__, "Failed to create shader resource view for texture. (HRESULT: {})");

    width = static_cast<unsigned short>(image.GetImages()[0].width);
    height = static_cast<unsigned short>(image.GetImages()[0].height);
}

AstrumTexture::AstrumTexture(const AstrumImage& image)
{
    if (FAILED(DirectX::CreateShaderResourceView(
        AstrumRenderer::Instance().GetDevice(),
        image.GetImages(),
        image.GetImageCount(),
        image.GetMetadata(),
        shaderResourceView.GetAddressOf()
    ))) throw AstrumException(__LINE__, __FILE__, "Failed to create shader resource view for texture. (HRESULT: {})");

    width = static_cast<unsigned short>(image.GetImages()[0].width);
    height = static_cast<unsigned short>(image.GetImages()[0].height);
}

ID3D11ShaderResourceView* AstrumTexture::GetShaderResourceView() const { return shaderResourceView.Get(); }
unsigned int AstrumTexture::GetWidth() const { return width; }
unsigned int AstrumTexture::GetHeight() const { return height; }
#include "AstrumTexture.hpp"

AstrumTexture::AstrumTexture(const std::wstring& path)
    : AstrumTexture(AstrumImage(path))
{
}

AstrumTexture::AstrumTexture(const AstrumImage& image)
{
    if (FAILED(DirectX::CreateShaderResourceView(
        AstrumRenderer::Instance().GetDevice(),
        image.GetImages(),
        image.GetImageCount(),
        image.GetMetadata(),
        &shaderResourceView)))
    {
        throw AstrumException(__LINE__, __FILE__, "Failed to create shader resource view for texture.");
	}

    width = static_cast<unsigned short>(image.GetImages()[0].width);
    height = static_cast<unsigned short>(image.GetImages()[0].height);
}

AstrumTexture::~AstrumTexture()
{
    if (shaderResourceView)
    {
        shaderResourceView->Release();
        shaderResourceView = nullptr;
    }
}

ID3D11ShaderResourceView* AstrumTexture::GetShaderResourceView() const { return shaderResourceView; }
unsigned int AstrumTexture::GetWidth() const { return width; }
unsigned int AstrumTexture::GetHeight() const { return height; }
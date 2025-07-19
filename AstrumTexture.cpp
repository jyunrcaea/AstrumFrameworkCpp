#include "AstrumTexture.hpp"

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
}

AstrumTexture::~AstrumTexture()
{
    if (shaderResourceView)
    {
        shaderResourceView->Release();
        shaderResourceView = nullptr;
    }
}

ID3D11ShaderResourceView* AstrumTexture::GetShaderResourceView() const
{
    return shaderResourceView;
}
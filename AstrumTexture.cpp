#include "AstrumTexture.hpp"

AstrumTexture::AstrumTexture(const std::string& filePath)
{
	ID3D11Device* const device = AstrumRenderer::Instance().GetDevice();
	ID3D11DeviceContext* const context = AstrumRenderer::Instance().GetContext();

    DirectX::ScratchImage image;
    if (FAILED(DirectX::LoadFromWICFile(
        std::wstring(filePath.begin(), filePath.end()).c_str(),
        DirectX::WIC_FLAGS_NONE,
        nullptr,
        image
    ))) {
        throw AstrumException("Failed to load texture from file: " + filePath);
    }

    if (FAILED(DirectX::CreateShaderResourceView(
        device,
        image.GetImages(),
        image.GetImageCount(),
        image.GetMetadata(),
        &shaderResourceView
    ))) {
        throw AstrumException("Failed to create shader resource view for texture: " + filePath);
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

#include "AstrumTexture.hpp"
#include <d3d11_1.h>
// Include necessary headers for image loading library (e.g., DirectXTex or WIC)
// #include <DirectXTex.h>

AstrumTexture::AstrumTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const std::string& filePath)
{
    // TODO: Implement image loading logic here.
    // Use a library like DirectXTex or WIC to load the image data from filePath.
    // Create an ID3D11Texture2D resource from the image data.
    // Create an ID3D11ShaderResourceView for the texture.
    // Assign the created shader resource view to m_shaderResourceView.

    // Example (conceptual, requires DirectXTex):
    // DirectX::TexMetadata metadata;
    // DirectX::ScratchImage scratchImage;
    // HRESULT hr = DirectX::LoadFromWICFile(filePath.c_str(), DirectX::WIC_FLAGS_NONE, &metadata, scratchImage);
    // if (SUCCEEDED(hr))
    // {
    //     hr = DirectX::CreateShaderResourceView(device, scratchImage.GetImages(), scratchImage.GetImageCount(), metadata, &m_shaderResourceView);
    // }
    // Handle errors appropriately
}

AstrumTexture::~AstrumTexture()
{
    // TODO: Release the DX11 texture resources.
    // Release the shader resource view.
    if (m_shaderResourceView)
    {
        m_shaderResourceView->Release();
        m_shaderResourceView = nullptr;
    }
    // If you stored the texture resource, release it here as well.
    // if (m_textureResource)
    // {
    //     m_textureResource->Release();
    //     m_textureResource = nullptr;
    // }
}

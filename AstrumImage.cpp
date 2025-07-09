#include "AstrumImage.hpp"
#include <Windows.h>
#include <wrl/client.h>

AstrumImage::AstrumImage(const std::string& filePath) {
    ID3D11Device* const device = AstrumRenderer::Instance().GetDevice();
    ID3D11DeviceContext* const context = AstrumRenderer::Instance().GetContext();

    // Convert std::string to std::wstring using MultiByteToWideChar
    int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, filePath.c_str(), -1, nullptr, 0);
    if (sizeNeeded == 0) {
        throw AstrumException(__LINE__, __FILE__, "Failed to convert file path to wide string.");
    }
    std::wstring wFilePath(sizeNeeded, 0);
    MultiByteToWideChar(CP_UTF8, 0, filePath.c_str(), -1, &wFilePath[0], sizeNeeded);

    HRESULT hr = DirectX::LoadFromWICFile(
        wFilePath.c_str(),
        DirectX::WIC_FLAGS_NONE,
        nullptr,
        image
    );

    if (FAILED(hr)) {
        throw AstrumException(__LINE__, __FILE__, "Failed to load image from file.");
    }
}

AstrumImage::~AstrumImage() {

}

size_t AstrumImage::GetWidth() const {
    return image.GetMetadata().width;
}

size_t AstrumImage::GetHeight() const {
    return image.GetMetadata().height;
}

DXGI_FORMAT AstrumImage::GetFormat() const {
    return image.GetMetadata().format;
}

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> AstrumImage::CreateShaderResourceView(ID3D11Device* pDevice) const {
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
    HRESULT hr = DirectX::CreateShaderResourceView(
        pDevice,
        image.GetImages(),
        image.GetImageCount(),
        image.GetMetadata(),
        srv.GetAddressOf()
    );
    if (FAILED(hr)) {
        throw AstrumException(__LINE__, __FILE__, "Failed to create shader resource view.");
    }
    return srv;
}
#include <d3d11_1.h>
#include <string>
#include <DirectXTex.h>
#include "AstrumRenderer.hpp"
#include "AstrumException.hpp"
#include <wincodec.h>

class AstrumImage
{
public:
    AstrumImage(const std::string& filePath);
    ~AstrumImage();

    const DirectX::ScratchImage& GetImage() const { return image; }

    size_t GetWidth() const;
    size_t GetHeight() const;
    DXGI_FORMAT GetFormat() const;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> CreateShaderResourceView(ID3D11Device* pDevice) const;

private:
    AstrumImage(const AstrumImage&) = delete;
    AstrumImage& operator=(const AstrumImage&) = delete;
    DirectX::ScratchImage image;
};
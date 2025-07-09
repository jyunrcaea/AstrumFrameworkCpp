#include <d3d11_1.h>
#include <string>
#include <DirectXTex.h>
#include "AstrumRenderer.hpp"
#include "AstrumException.hpp"

class AstrumTexture
{
public:
    AstrumTexture(const std::string& filePath);
    ~AstrumTexture();

    ID3D11ShaderResourceView* GetShaderResourceView() const;

private:
    AstrumTexture(const AstrumTexture&) = delete;
    AstrumTexture& operator=(const AstrumTexture&) = delete;

    ID3D11ShaderResourceView* shaderResourceView = nullptr;
};
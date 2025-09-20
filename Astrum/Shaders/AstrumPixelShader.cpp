#include "../Shaders/AstrumPixelShader.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"
#include "../Resources/AstrumMaterial.hpp"

AstrumPixelShader::AstrumPixelShader(const std::wstring& path, const std::string& entryPoint, const std::string& profile) : AstrumShader(path, entryPoint, profile)
{
    if (FAILED(AstrumRenderer::Instance().GetDevice()->CreatePixelShader(
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader
    ))) AstrumException(__LINE__, __FILE__, "CreatePixelShader failed.").Alert();
}

void AstrumPixelShader::SetShader() {
    AstrumRenderer::Instance().GetContext()->PSSetShader(shader.Get(), nullptr, 0);
}

ID3D11PixelShader* AstrumPixelShader::GetPixelShader() const {
    return shader.Get();
}
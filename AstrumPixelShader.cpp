#include "AstrumPixelShader.hpp"
#include "AstrumRenderer.hpp"
#include "AstrumException.hpp"

AstrumPixelShader::AstrumPixelShader(const std::wstring& path,
    const std::string& entryPoint,
    const std::string& profile)
    : AstrumShader(path, entryPoint, profile)
{
    if (FAILED(AstrumRenderer::Instance().GetDevice()->CreatePixelShader(
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader)))
    {
        throw AstrumException("CreatePixelShader failed.");
    }
}

void AstrumPixelShader::SetShader() {
    AstrumRenderer::Instance().GetContext()->PSSetShader(shader.Get(), nullptr, 0);
}

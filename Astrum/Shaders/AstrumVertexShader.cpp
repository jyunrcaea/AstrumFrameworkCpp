#include "AstrumVertexShader.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

AstrumVertexShader::AstrumVertexShader(const std::wstring& path,
    const std::string& entryPoint,
    const std::string& profile)
    : AstrumShader(path, entryPoint, profile)
{
    if (FAILED(AstrumRenderer::Instance().GetDevice()->CreateVertexShader(
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader
    ))) {
        AstrumException(__LINE__, __FILE__, "CreateVertexShader failed.").Alert();
    }
}

void AstrumVertexShader::SetShader() {
    AstrumRenderer::Instance().GetContext()->VSSetShader(shader.Get(), nullptr, 0);
}
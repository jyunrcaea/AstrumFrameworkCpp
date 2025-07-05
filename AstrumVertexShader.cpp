#include "AstrumVertexShader.hpp"
#include "AstrumRenderer.hpp"
#include "AstrumException.hpp"

AstrumVertexShader::AstrumVertexShader(const std::wstring& path,
    const std::string& entryPoint,
    const std::string& profile)
    : AstrumShader(path, entryPoint, profile)
{
    if (FAILED(AstrumRenderer::Instance().GetDevice()->CreateVertexShader(
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader)))
    {
        throw AstrumException("CreateVertexShader failed.");
    }
}

void AstrumVertexShader::SetShader() {
    AstrumRenderer::Instance().GetContext()->VSSetShader(shader.Get(), nullptr, 0);
}

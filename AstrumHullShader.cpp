#include "AstrumHullShader.hpp"
#include "AstrumRenderer.hpp"
#include "AstrumException.hpp"

AstrumHullShader::AstrumHullShader(const std::wstring& path,
    const std::string& entryPoint,
    const std::string& profile)
    : AstrumShader(path, entryPoint, profile)
{
    if (FAILED(AstrumRenderer::Instance().GetDevice()->CreateHullShader(
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader)))
    {
        throw AstrumException("CreateHullShader failed.");
    }
}

void AstrumHullShader::SetShader() {
    AstrumRenderer::Instance().GetContext()->HSSetShader(shader.Get(), nullptr, 0);
}

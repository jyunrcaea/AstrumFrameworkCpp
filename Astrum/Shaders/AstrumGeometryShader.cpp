#include "AstrumGeometryShader.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

AstrumGeometryShader::AstrumGeometryShader(const std::wstring& path, const std::string& entryPoint, const std::string& profile)
    : AstrumShader(path, entryPoint, profile)
{
    if (FAILED(AstrumRenderer::Instance().GetDevice()->CreateGeometryShader(
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader)))
    {
        throw AstrumException("CreateGeometryShader failed.");
    }
}

void AstrumGeometryShader::SetShader() {
    AstrumRenderer::Instance().GetContext()->GSSetShader(shader.Get(), nullptr, 0);
}

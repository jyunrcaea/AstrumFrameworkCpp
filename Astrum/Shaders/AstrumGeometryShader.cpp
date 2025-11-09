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
        &shader
    ))) AstrumException("CreateGeometryShader failed.").Alert();
}

AstrumGeometryShader::AstrumGeometryShader(const char* shaderCode, size_t shaderCodeLength, const std::string& entryPoint, const std::string& profile)
    : AstrumShader(shaderCode, shaderCodeLength, entryPoint, profile)
{
    if (FAILED(AstrumRenderer::Instance().GetDevice()->CreateGeometryShader(
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader
    ))) AstrumException("CreateGeometryShader failed.").Alert();
}

void AstrumGeometryShader::SetShader() {
    AstrumRenderer::Instance().GetContext()->GSSetShader(shader.Get(), nullptr, 0);
}

#include "AstrumDomainShader.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

AstrumDomainShader::AstrumDomainShader(const std::wstring& path, const std::string& entryPoint, const std::string& profile)
    : AstrumShader(path, entryPoint, profile)
{
    if (FAILED(AstrumRenderer::Instance().GetDevice()->CreateDomainShader(
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader
    ))) AstrumException("CreateDomainShader failed.").Alert();
}

AstrumDomainShader::AstrumDomainShader(const char* shaderCode, size_t shaderCodeLength, const std::string& entryPoint, const std::string& profile)
    : AstrumShader(shaderCode, shaderCodeLength, entryPoint, profile)
{
    if (FAILED(AstrumRenderer::Instance().GetDevice()->CreateDomainShader(
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader
    ))) AstrumException("CreateDomainShader failed.").Alert();
}

void AstrumDomainShader::SetShader() {
    AstrumRenderer::Instance().GetContext()->DSSetShader(shader.Get(), nullptr, 0);
}

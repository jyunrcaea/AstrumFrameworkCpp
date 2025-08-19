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
        &shader)))
    {
        throw AstrumException("CreateDomainShader failed.");
    }
}

void AstrumDomainShader::SetShader() {
    AstrumRenderer::Instance().GetContext()->DSSetShader(shader.Get(), nullptr, 0);
}

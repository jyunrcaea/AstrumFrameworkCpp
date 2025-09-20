#include "AstrumHullShader.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

AstrumHullShader::AstrumHullShader(const std::wstring& path, const std::string& entryPoint, const std::string& profile)
    : AstrumShader(path, entryPoint, profile)
{
    if (FAILED(AstrumRenderer::Instance().GetDevice()->CreateHullShader(
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader
    ))) AstrumException(__LINE__, __FILE__, "CreateHullShader failed.").Alert();
}

void AstrumHullShader::SetShader() {
    AstrumRenderer::Instance().GetContext()->HSSetShader(shader.Get(), nullptr, 0);
}

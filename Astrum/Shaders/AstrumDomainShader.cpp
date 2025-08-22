#include "AstrumDomainShader.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

namespace Astrum
{
	DomainShader::DomainShader(const std::wstring& path, const std::string& entryPoint, const std::string& profile)
		: Shader(path, entryPoint, profile)
	{
		if (FAILED(Renderer::Instance().GetDevice()->CreateDomainShader(
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			nullptr,
			&shader)))
		{
			throw Exception("CreateDomainShader failed.");
		}
	}

	void DomainShader::SetShader() {
		Renderer::Instance().GetContext()->DSSetShader(shader.Get(), nullptr, 0);
	}
}

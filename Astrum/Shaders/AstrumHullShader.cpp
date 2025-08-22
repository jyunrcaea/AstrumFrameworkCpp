#include "AstrumHullShader.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

namespace Astrum
{
	HullShader::HullShader(const std::wstring& path, const std::string& entryPoint, const std::string& profile)
		: Shader(path, entryPoint, profile)
	{
		if (FAILED(Renderer::Instance().GetDevice()->CreateHullShader(
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			nullptr,
			&shader)))
		{
			throw Exception("CreateHullShader failed.");
		}
	}

	void HullShader::SetShader() {
		Renderer::Instance().GetContext()->HSSetShader(shader.Get(), nullptr, 0);
	}
}

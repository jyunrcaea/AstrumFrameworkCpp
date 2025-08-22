#include "AstrumVertexShader.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

namespace Astrum
{
	VertexShader::VertexShader(const std::wstring& path,
		const std::string& entryPoint,
		const std::string& profile)
		: Shader(path, entryPoint, profile)
	{
		if (FAILED(Renderer::Instance().GetDevice()->CreateVertexShader(
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			nullptr,
			&shader)))
		{
			throw Exception("CreateVertexShader failed.");
		}
	}

	void VertexShader::SetShader() {
		Renderer::Instance().GetContext()->VSSetShader(shader.Get(), nullptr, 0);
	}
}
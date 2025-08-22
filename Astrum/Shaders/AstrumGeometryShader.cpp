#include "AstrumGeometryShader.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"

namespace Astrum
{
	GeometryShader::GeometryShader(const std::wstring& path, const std::string& entryPoint, const std::string& profile)
		: Shader(path, entryPoint, profile)
	{
		if (FAILED(Renderer::Instance().GetDevice()->CreateGeometryShader(
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			nullptr,
			&shader)))
		{
			throw Exception("CreateGeometryShader failed.");
		}
	}

	void GeometryShader::SetShader() {
		Renderer::Instance().GetContext()->GSSetShader(shader.Get(), nullptr, 0);
	}
}

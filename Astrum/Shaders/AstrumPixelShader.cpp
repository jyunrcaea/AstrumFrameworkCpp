#include "../Shaders/AstrumPixelShader.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"
#include "../Resources/AstrumMaterial.hpp"

namespace Astrum
{
	PixelShader::PixelShader(const std::wstring& path, const std::string& entryPoint, const std::string& profile) : Shader(path, entryPoint, profile)
	{
		if (FAILED(Renderer::Instance().GetDevice()->CreatePixelShader(
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			nullptr,
			&shader)))
		{
			throw Exception("CreatePixelShader failed.");
		}
	}

	void PixelShader::SetShader() {
		Renderer::Instance().GetContext()->PSSetShader(shader.Get(), nullptr, 0);
	}

	ID3D11PixelShader* PixelShader::GetPixelShader() const {
		return shader.Get();
	}
}
#include "AstrumTexture.hpp"
#include "../AstrumException.hpp"

namespace Astrum
{
	Texture::Texture(const std::wstring& path)
		: Texture(Image(path))
	{
	}

	Texture::Texture(const Image& image)
	{
		if (FAILED(DirectX::CreateShaderResourceView(
			Renderer::Instance().GetDevice(),
			image.GetImages(),
			image.GetImageCount(),
			image.GetMetadata(),
			shaderResourceView.GetAddressOf()
		))) {
			throw Exception(__LINE__, __FILE__, "Failed to create shader resource view for texture. (HRESULT: {})");
		}
		width = static_cast<unsigned short>(image.GetImages()[0].width);
		height = static_cast<unsigned short>(image.GetImages()[0].height);
	}

	ID3D11ShaderResourceView* Texture::GetShaderResourceView() const { return shaderResourceView.Get(); }
	unsigned int Texture::GetWidth() const { return width; }
	unsigned int Texture::GetHeight() const { return height; }
}
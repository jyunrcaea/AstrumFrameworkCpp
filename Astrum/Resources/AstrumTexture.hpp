#pragma once
#include <d3d11_1.h>
#include <wrl/client.h>
#include <string>
#include "AstrumImage.hpp"
#include "../Singletons/AstrumRenderer.hpp"
#include "IAstrumTexture.hpp"

using Microsoft::WRL::ComPtr;

namespace Astrum
{
	class Image;

	class Texture : public ITexture
	{
	private:
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

	public:
		Texture(const std::wstring& path);
		Texture(const Image& image);

		virtual ID3D11ShaderResourceView* GetShaderResourceView() const override;
		virtual unsigned int GetWidth() const override;
		virtual unsigned int GetHeight() const override;
	private:
		ComPtr<ID3D11ShaderResourceView> shaderResourceView;
		unsigned int width = 0, height = 0;

	public:
		static std::shared_ptr<Texture> MakeShared(const std::wstring& path) { return std::make_shared<Texture>(path); }
		static std::shared_ptr<Texture> MakeShared(const Image& image) { return std::make_shared<Texture>(image); }
	};
}
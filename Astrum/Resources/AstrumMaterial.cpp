#include "AstrumMaterial.hpp"
#include "AstrumTexture.hpp"

namespace Astrum
{
	Material::Material(const std::wstring& path)
		: Material(Texture::MakeShared(path))
	{
	}

	Material::Material(const std::shared_ptr<ITexture>& texturePtr)
		: texture(texturePtr) {
		SetupTextureSize();
	}

	Material::Material(std::shared_ptr<ITexture>&& texturePtr)
		: texture(std::move(texturePtr)) {
		SetupTextureSize();
	}

	void Material::SetTexture(const std::shared_ptr<ITexture>& newTexture) {
		texture = newTexture;
		SetupTextureSize();
	}

	void Material::SetTexture(std::shared_ptr<ITexture>&& newTexture) {
		texture = std::move(newTexture);
		SetupTextureSize();
	}

	void Material::SetupTextureSize() {
		SetSize(
			static_cast<unsigned short>(texture->GetWidth()),
			static_cast<unsigned short>(texture->GetHeight())
		);
	}
}

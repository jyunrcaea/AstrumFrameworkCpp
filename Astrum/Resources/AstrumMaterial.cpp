#include "AstrumMaterial.hpp"
#include "AstrumTexture.hpp"

AstrumMaterial::AstrumMaterial(const std::wstring& path)
	: AstrumMaterial(AstrumTexture::MakeShared(path))
{
}

AstrumMaterial::AstrumMaterial(const std::shared_ptr<IAstrumTexture>& texturePtr)
	: texture(texturePtr) {
	SetupTextureSize();
}

AstrumMaterial::AstrumMaterial(std::shared_ptr<IAstrumTexture>&& texturePtr)
	: texture(std::move(texturePtr)) {
	SetupTextureSize();
}

void AstrumMaterial::SetTexture(const std::shared_ptr<IAstrumTexture>& newTexture) {
	texture = newTexture;
	SetupTextureSize();
}

void AstrumMaterial::SetTexture(std::shared_ptr<IAstrumTexture>&& newTexture) {
	texture = std::move(newTexture);
	SetupTextureSize();
}

void AstrumMaterial::SetupTextureSize() {
	SetSize(
		static_cast<unsigned short>(texture->GetWidth()),
		static_cast<unsigned short>(texture->GetHeight())
	);
}

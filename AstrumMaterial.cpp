#include "AstrumMaterial.hpp"

AstrumMaterial::AstrumMaterial(const std::wstring& path)
	: AstrumMaterial(std::make_shared<AstrumTexture>(path))
{
}

AstrumMaterial::AstrumMaterial(const std::shared_ptr<AstrumTexture>& texture) {
	this->texture = texture;
	SetSize(
		static_cast<unsigned short>(texture->GetWidth()),
		static_cast<unsigned short>(texture->GetHeight())
	);
}
AstrumMaterial::~AstrumMaterial() { }

AstrumTexture& AstrumMaterial::GetTexture() const { return *texture; }
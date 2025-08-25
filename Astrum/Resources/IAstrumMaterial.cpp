#include "IAstrumMaterial.hpp"
#include <vector>
#include "../Vectors/AstrumVector2.hpp"
#include "../Vectors/AstrumVector3.hpp"
#include "../Units/AstrumTextureVertex.hpp"

IAstrumMaterial::IAstrumMaterial() { }

unsigned int IAstrumMaterial::GetTextureWidth() const {
	return GetTexture()->GetWidth();
}

unsigned int IAstrumMaterial::GetTextureHeight() const {
	return GetTexture()->GetHeight();
}

std::shared_ptr<AstrumTextureMesh> IAstrumMaterial::CreateTextureSizeMesh(float z) const {
	const float halfWidth = static_cast<float>(GetTextureWidth() * 0.5);
	const float halfHeight = static_cast<float>(GetTextureHeight() * 0.5);
	return AstrumTextureMesh::MakeShared(
		AstrumVector3{ -halfWidth, halfHeight, z},
		AstrumVector3{ halfWidth, halfHeight, z},
		AstrumVector3{ -halfWidth, -halfHeight, z},
		AstrumVector3{ halfWidth, -halfHeight, z}
	);
}

std::shared_ptr<AstrumTextureMesh> IAstrumMaterial::CreateCustomSizeMesh(uint left, uint top, uint width, uint height, float z) const {
	const double textureWidth = static_cast<double>(GetTextureWidth());
	const double textureHeight = static_cast<double>(GetTextureHeight());

	return CreateCustomSizeMeshFromRatio(
		static_cast<float>(static_cast<double>(left) / textureWidth),
		static_cast<float>(static_cast<double>(top) / textureHeight),
		static_cast<float>(static_cast<double>(left + width) / textureWidth),
		static_cast<float>(static_cast<double>(top + height) / textureHeight),
		z
	);
}

std::shared_ptr<AstrumTextureMesh> IAstrumMaterial::CreateCustomSizeMeshFromRatio(float left, float top, float right, float bottom, float z) const {
	const float halfWidth = static_cast<float>(GetTextureWidth() * 0.5);
	const float halfHeight = static_cast<float>(GetTextureHeight() * 0.5);

	return AstrumTextureMesh::MakeShared(std::vector<AstrumTextureVertex>{
		AstrumTextureVertex{ AstrumVector3(-halfWidth, halfHeight, z), AstrumVector2(left, bottom) },
			AstrumTextureVertex{ AstrumVector3(halfWidth, halfHeight, z), AstrumVector2(right, bottom) },
			AstrumTextureVertex{ AstrumVector3(-halfWidth, -halfHeight, z), AstrumVector2(left, top) },
			AstrumTextureVertex{ AstrumVector3(halfWidth, -halfHeight, z), AstrumVector2(right, top) },
	}, std::vector<unsigned short>{ 0, 1, 2, 1, 3, 2 });
}
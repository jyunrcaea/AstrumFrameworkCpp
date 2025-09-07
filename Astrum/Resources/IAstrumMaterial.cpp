#include "IAstrumMaterial.hpp"
#include <vector>
#include "../Vectors/AstrumVector2.hpp"
#include "../Vectors/AstrumVector3.hpp"
#include "../Units/AstrumTextureVertex.hpp"

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
	const float width = static_cast<float>(GetTextureWidth());
	const float height = static_cast<float>(GetTextureHeight());
	const float halfWidth = static_cast<float>(width * 0.5);
	const float halfHeight = static_cast<float>(height * 0.5);

	return AstrumTextureMesh::MakeShared(std::vector<AstrumTextureVertex>{
		AstrumTextureVertex{ AstrumVector3(-halfWidth + (width * left), halfHeight - (height * top), z), AstrumVector2(left, top)}, //(-0.5, 0.5)
		AstrumTextureVertex{ AstrumVector3(halfWidth - (width * (1.0f - right)), halfHeight - (height * top), z), AstrumVector2(right, top) }, //(0.5, 0.5)
		AstrumTextureVertex{ AstrumVector3(-halfWidth + (width * left), -halfHeight + (height * (1.0f - bottom)), z), AstrumVector2(left, bottom) }, //(-0.5, -0.5)
		AstrumTextureVertex{ AstrumVector3(halfWidth - (width * (1.0f - right)), -halfHeight + (height * (1.0f - bottom)), z), AstrumVector2(right, bottom) }, //(0.5, -0.5)
	}, std::vector<unsigned short>{ 0, 1, 2, 1, 3, 2 });
}
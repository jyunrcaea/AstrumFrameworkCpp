#include "IAstrumTexture.hpp"
#include "../Meshes/AstrumTextureMesh.hpp"
#include "../Vectors/AstrumVector3.hpp"

std::shared_ptr<AstrumTextureMesh> IAstrumTexture::CreateTextureSizeMesh(float z) const {
	const float halfWidth = static_cast<float>(GetWidth() * 0.5);
	const float halfHeight = static_cast<float>(GetHeight() * 0.5);
	return AstrumTextureMesh::MakeShared(
		AstrumVector3{ -halfWidth, halfHeight, z },
		AstrumVector3{ halfWidth, halfHeight, z },
		AstrumVector3{ -halfWidth, -halfHeight, z },
		AstrumVector3{ halfWidth, -halfHeight, z }
	);
}
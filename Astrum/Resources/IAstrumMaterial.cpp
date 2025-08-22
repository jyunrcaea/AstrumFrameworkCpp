#include "IAstrumMaterial.hpp"
#include <vector>
#include "../Vectors/AstrumVector2.hpp"
#include "../Vectors/AstrumVector3.hpp"
#include "../Units/AstrumTextureVertex.hpp"

namespace Astrum
{
	IMaterial::IMaterial() { }

	unsigned int IMaterial::GetTextureWidth() const {
		return GetTexture()->GetWidth();
	}

	unsigned int IMaterial::GetTextureHeight() const {
		return GetTexture()->GetHeight();
	}

	std::shared_ptr<TextureMesh> IMaterial::CreateTextureSizeMesh(float z) const {
		const float halfWidth = static_cast<float>(GetTextureWidth() * 0.5);
		const float halfHeight = static_cast<float>(GetTextureHeight() * 0.5);
		return TextureMesh::MakeShared(
			Vector3{ -halfWidth, halfHeight, z },
			Vector3{ halfWidth, halfHeight, z },
			Vector3{ -halfWidth, -halfHeight, z },
			Vector3{ halfWidth, -halfHeight, z }
		);
	}

	std::shared_ptr<TextureMesh> IMaterial::CreateCustomSizeMesh(uint left, uint top, uint width, uint height, float z) const {
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

	std::shared_ptr<TextureMesh> IMaterial::CreateCustomSizeMeshFromRatio(float left, float top, float right, float bottom, float z) const {
		const float halfWidth = static_cast<float>(GetTextureWidth() * 0.5);
		const float halfHeight = static_cast<float>(GetTextureHeight() * 0.5);

		return TextureMesh::MakeShared(std::vector<TextureVertex>{
			TextureVertex{ Vector3(-halfWidth, halfHeight, z), Vector2(left, bottom) },
				TextureVertex{ Vector3(halfWidth, halfHeight, z), Vector2(right, bottom) },
				TextureVertex{ Vector3(-halfWidth, -halfHeight, z), Vector2(left, top) },
				TextureVertex{ Vector3(halfWidth, -halfHeight, z), Vector2(right, top) },
		}, std::vector<unsigned short>{ 0, 1, 2, 1, 3, 2 });
	}
}
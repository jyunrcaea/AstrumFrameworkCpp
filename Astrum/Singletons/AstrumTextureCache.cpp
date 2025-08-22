#include "AstrumTextureCache.hpp"

namespace Astrum {
	std::shared_ptr<Texture> TextureCacheSingleton::Load(const std::filesystem::path& path)
	{
		std::wstring name;
		if (path.is_absolute()) name = path;
		else name = std::filesystem::absolute(DefaultRelativeDirectory / path);

		std::shared_ptr<Texture> texture;
		if (textureMap.contains(name) && (texture = textureMap[name].lock())) {
			return texture;
		}
		textureMap[name] = texture = Texture::MakeShared(name);
		return texture;
	}

	void TextureCacheSingleton::CleanUp() {
		for (auto it = textureMap.begin(); it != textureMap.end();) {
			if (it->second.expired()) {
				it = textureMap.erase(it);
			}
			else {
				++it;
			}
		}
	}
}
#include "AstrumTextureCache.hpp"

std::shared_ptr<AstrumTexture> AstrumTextureCacheSingleton::Load(const std::filesystem::path& path)
{
	return LoadTextureFromAbsolutePath(
        path.is_absolute() ? path : std::filesystem::absolute(DefaultRelativeDirectory / path)
    );
}
std::shared_ptr<AstrumTexture> AstrumTextureCacheSingleton::Load(std::filesystem::path&& path)
{
    return LoadTextureFromAbsolutePath(
        path.is_absolute() ? std::move(path) : std::filesystem::absolute(DefaultRelativeDirectory / path)
    );
}

void AstrumTextureCacheSingleton::CleanUp() {
    for (auto it = textureMap.begin(); it != textureMap.end();) {
        if (it->second.expired()) {
            it = textureMap.erase(it);
        } else {
            ++it;
        }
	}
}

std::shared_ptr<AstrumTexture> AstrumTextureCacheSingleton::LoadTextureFromAbsolutePath(std::wstring&& name) {
    std::shared_ptr<AstrumTexture> texture;
    if (textureMap.contains(name) && (texture = textureMap[name].lock())) {
        return texture;
    }
    textureMap[name] = texture = AstrumTexture::MakeShared(name);
    return texture;
}
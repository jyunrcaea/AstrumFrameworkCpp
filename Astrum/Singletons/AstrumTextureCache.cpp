#include "AstrumTextureCache.hpp"

std::shared_ptr<AstrumTexture> AstrumTextureCacheSingleton::Load(const std::filesystem::path& path)
{
    std::wstring name;
    if (path.is_absolute()) name = path;
    else name= std::filesystem::absolute(DefaultRelativeDirectory / path);

    std::shared_ptr<AstrumTexture> texture;
    if (textureMap.contains(name) && (texture = textureMap[name].lock())) {
        return texture;
    }
	textureMap[name] = texture = AstrumTexture::MakeShared(name);
    return texture;
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
#include "AstrumTextureCache.hpp"

std::shared_ptr<AstrumTexture>& AstrumTextureCacheSingleton::Load(const std::filesystem::path& path)
{
    std::wstring name;
    if (path.is_absolute()) name = path;
    else name= std::filesystem::absolute(DefaultRelativeDirectory / path);

    if (textureMap.contains(name)) return textureMap[name];
    return textureMap[name] = AstrumTexture::MakeShared(name);
}
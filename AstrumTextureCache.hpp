#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <filesystem>
#include "AstrumSingleton.hpp"
#include "AstrumTexture.hpp"

class AstrumTextureCacheSingleton : public AstrumSingleton<AstrumTextureCacheSingleton> {
    friend class AstrumSingleton<AstrumTextureCacheSingleton>;
    friend class AstrumTextureCache;
public:
    std::shared_ptr<AstrumTexture>& Load(const std::filesystem::path& path);
    std::filesystem::path DefaultRelativeDirectory = L"./Assets/";
private:
    std::unordered_map<std::wstring, std::shared_ptr<AstrumTexture>> textureMap;
};

class AstrumTextureCache {
    AstrumTextureCache() = delete;
public:
    static inline std::shared_ptr<AstrumTexture>& Load(const std::filesystem::path& path) { return AstrumTextureCacheSingleton::Instance().Load(path); }
    static inline std::filesystem::path& DefaultRelativeDirectory() { return AstrumTextureCacheSingleton::Instance().DefaultRelativeDirectory; }
};
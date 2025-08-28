#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <filesystem>
#include "AstrumSingleton.hpp"
#include "../Resources/AstrumTexture.hpp"

class AstrumTextureCacheSingleton : public AstrumSingleton<AstrumTextureCacheSingleton> {
    friend class AstrumSingleton<AstrumTextureCacheSingleton>;
    friend class AstrumTextureCache;
public:
    std::shared_ptr<AstrumTexture> Load(const std::filesystem::path& path);
    std::shared_ptr<AstrumTexture> Load(std::filesystem::path&& path);
    void CleanUp();
	// 기본적으로 상대 경로로 Game/Assets 폴더를 사용합니다.
    std::filesystem::path DefaultRelativeDirectory = L"./Game/Assets/";
private:
    std::unordered_map<std::wstring, std::weak_ptr<AstrumTexture>> textureMap;
    std::shared_ptr<AstrumTexture> LoadTextureFromAbsolutePath(std::wstring&& path);
};

class AstrumTextureCache {
    AstrumTextureCache() = delete;
public:
	// 주어진 경로의 텍스쳐를 로드합니다. 경로는 절대 경로 또는 상대 경로를 사용할 수 있습니다.
    static inline std::shared_ptr<AstrumTexture> Load(const std::filesystem::path& path) { return AstrumTextureCacheSingleton::Instance().Load(path); }
    static inline std::shared_ptr<AstrumTexture> Load(std::filesystem::path&& path) { return AstrumTextureCacheSingleton::Instance().Load(std::move(path)); }
	// 만료된 텍스쳐 참조를 모두 정리합니다.
	static inline void CleanUp() { AstrumTextureCacheSingleton::Instance().CleanUp(); }
	// 텍스쳐가 상대 경로로 로드될때 사용할 기준 상대경로를 반환합니다.
    static std::filesystem::path& GetDefaultRelativeDirectory() { return AstrumTextureCacheSingleton::Instance().DefaultRelativeDirectory; }
	// 텍스쳐가 상대 경로로 로드될때 사용할 기준 상대경로를 설정합니다.
    static void SetDefaultRelativeDirectory(const std::filesystem::path& path) { AstrumTextureCacheSingleton::Instance().DefaultRelativeDirectory = path; }
    static void SetDefaultRelativeDirectory(std::filesystem::path&& path) { AstrumTextureCacheSingleton::Instance().DefaultRelativeDirectory = std::move(path); }
};
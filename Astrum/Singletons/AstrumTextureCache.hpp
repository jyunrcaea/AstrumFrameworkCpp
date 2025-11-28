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
    /// <summary>
    /// 주어진 경로에서 텍스처를 로드합니다. 캐시에 이미 로드된 텍스처가 있으면 재사용합니다.
    /// </summary>
    /// <typeparam name="PathType">filesystem::path 타입입니다.</typeparam>
    /// <param name="path">텍스처 파일의 절대 경로 또는 상대 경로입니다.</param>
    /// <returns>로드된 텍스처의 공유 포인터입니다.</returns>
    template <typename PathType>
    requires std::same_as<std::remove_cvref_t<PathType>, std::filesystem::path>
    std::shared_ptr<AstrumTexture> Load(PathType&& path);
    /// <summary>
    /// 만료된 텍스처 참조를 모두 캐시에서 정리합니다.
    /// </summary>
    void CleanUp();
    /// <summary>
    /// 텍스처가 상대 경로로 로드될 때 사용할 기본 상대 경로입니다. 기본값은 "./Game/Assets/"입니다.
    /// </summary>
    std::filesystem::path DefaultRelativeDirectory = L"./Game/Assets/";
private:
    std::unordered_map<std::wstring, std::shared_ptr<AstrumTexture>> textureMap;
};

class AstrumTextureCache {
    AstrumTextureCache() = delete;
public:
	/// <summary>
	/// 주어진 경로에서 텍스처를 로드합니다. 캐시에 이미 로드된 텍스처가 있으면 재사용합니다. 절대 경로 또는 상대 경로를 사용할 수 있습니다.
	/// </summary>
	/// <param name="path">텍스처 파일의 경로입니다.</param>
	/// <returns>로드된 텍스처의 공유 포인터입니다.</returns>
    static inline std::shared_ptr<AstrumTexture> Load(const std::filesystem::path& path) { return AstrumTextureCacheSingleton::Instance().Load(path); }
    /// <summary>
	/// 주어진 경로에서 텍스처를 로드합니다. 캐시에 이미 로드된 텍스처가 있으면 재사용합니다. 절대 경로 또는 상대 경로를 사용할 수 있습니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="path">텍스처 파일의 경로입니다.</param>
	/// <returns>로드된 텍스처의 공유 포인터입니다.</returns>
    static inline std::shared_ptr<AstrumTexture> Load(std::filesystem::path&& path) { return AstrumTextureCacheSingleton::Instance().Load(std::move(path)); }
	/// <summary>
	/// 만료된 텍스처 참조를 모두 캐시에서 정리합니다.
	/// </summary>
	static inline void CleanUp() { AstrumTextureCacheSingleton::Instance().CleanUp(); }
	/// <summary>
	/// 텍스처가 상대 경로로 로드될 때 사용할 기본 상대 경로를 반환합니다.
	/// </summary>
	/// <returns>기본 상대 경로입니다.</returns>
    static std::filesystem::path& GetDefaultRelativeDirectory() { return AstrumTextureCacheSingleton::Instance().DefaultRelativeDirectory; }
	/// <summary>
	/// 텍스처가 상대 경로로 로드될 때 사용할 기본 상대 경로를 설정합니다.
	/// </summary>
	/// <param name="path">설정할 기본 상대 경로입니다.</param>
    static void SetDefaultRelativeDirectory(const std::filesystem::path& path) { AstrumTextureCacheSingleton::Instance().DefaultRelativeDirectory = path; }
    /// <summary>
	/// 텍스처가 상대 경로로 로드될 때 사용할 기본 상대 경로를 설정합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="path">설정할 기본 상대 경로입니다.</param>
    static void SetDefaultRelativeDirectory(std::filesystem::path&& path) { AstrumTextureCacheSingleton::Instance().DefaultRelativeDirectory = std::move(path); }
};

template<typename PathType>
requires std::same_as<std::remove_cvref_t<PathType>, std::filesystem::path>
inline std::shared_ptr<AstrumTexture> AstrumTextureCacheSingleton::Load(PathType&& path) {
    std::wstring name{
        std::forward<PathType>(path).is_absolute() ? std::forward<PathType>(path) : std::filesystem::canonical(DefaultRelativeDirectory / std::forward<PathType>(path))
    };
    if (false == textureMap.contains(name)) {
        textureMap.insert({ name , AstrumTexture::MakeShared(name) });
    }
    return textureMap[name];
}
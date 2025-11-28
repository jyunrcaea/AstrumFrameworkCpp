#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <filesystem>
#include "AstrumSingleton.hpp"
#include "../Resources/AstrumFonts.hpp"

/// <summary>
/// 글꼴 리소스를 캐시하는 싱글톤 클래스입니다.
/// 로드된 글꼴을 메모리에 보관하여 중복 로드를 방지합니다.
/// </summary>
class AstrumFontsCacheSingleton : public AstrumSingleton<AstrumFontsCacheSingleton>
{
	friend class AstrumSingleton<AstrumFontsCacheSingleton>;

public:
    /// <summary>
    /// 지정된 경로의 글꼴 컬렉션을 로드합니다.
    /// 절대 경로 또는 상대 경로를 사용할 수 있습니다.
    /// 이미 로드된 글꼴은 캐시에서 반환됩니다.
    /// </summary>
    /// <typeparam name="PathType">std::filesystem::path 타입입니다.</typeparam>
    /// <param name="path">로드할 글꼴 파일의 경로입니다.</param>
    /// <returns>로드된 글꼴 컬렉션의 공유 포인터입니다.</returns>
    template <typename PathType>
    requires std::same_as<std::remove_cvref_t<PathType>, std::filesystem::path>
    std::shared_ptr<AstrumFonts> Load(PathType&& path);
    /// <summary>
    /// 캐시에서 만료된 글꼴 컬렉션 참조를 모두 정리합니다.
    /// 더 이상 참조되지 않는 글꼴이 메모리에서 해제됩니다.
    /// </summary>
    void CleanUp();
    /// <summary>
    /// 글꼴 컬렉션이 상대 경로로 로드될 때 사용할 기준 상대경로입니다.
    /// 기본값은 L"./Game/Assets/"입니다.
    /// </summary>
    std::filesystem::path DefaultRelativeDirectory = L"./Game/Assets/";
private:
    /// <summary>
    /// 로드된 글꼴 컬렉션을 저장하는 캐시 맵입니다.
    /// 키는 글꼴 경로(절대경로로 정규화됨)이고, 값은 글꼴 컬렉션 공유 포인터입니다.
    /// </summary>
    std::unordered_map<std::wstring, std::shared_ptr<AstrumFonts>> fontsMap;
};

/// <summary>
/// 글꼴 캐시에 접근하기 위한 정적 인터페이스입니다.
/// AstrumFontsCacheSingleton의 싱글톤 인스턴스에 쉽게 접근할 수 있습니다.
/// </summary>
class AstrumFontsCache
{
    /// <summary>
    /// 생성자를 삭제하여 인스턴스화를 방지합니다.
    /// </summary>
    AstrumFontsCache() = delete;
public:
    /// <summary>
    /// 지정된 경로의 글꼴 컬렉션을 로드합니다. (절대 경로 또는 상대 경로)
    /// </summary>
    /// <param name="path">로드할 글꼴 파일의 경로입니다.</param>
    /// <returns>로드된 글꼴 컬렉션의 공유 포인터입니다.</returns>
    static inline std::shared_ptr<AstrumFonts> Load(const std::filesystem::path& path) { return AstrumFontsCacheSingleton::Instance().Load(path); }
    /// <summary>
    /// 지정된 경로의 글꼴 컬렉션을 로드합니다. (우측값 참조 버전)
    /// </summary>
    /// <param name="path">로드할 글꼴 파일의 경로입니다.</param>
    /// <returns>로드된 글꼴 컬렉션의 공유 포인터입니다.</returns>
    static inline std::shared_ptr<AstrumFonts> Load(std::filesystem::path&& path) { return AstrumFontsCacheSingleton::Instance().Load(std::move(path)); }
    /// <summary>
    /// 캐시에서 만료된 글꼴 컬렉션 참조를 모두 정리합니다.
    /// </summary>
    static inline void CleanUp() { AstrumFontsCacheSingleton::Instance().CleanUp(); }
    /// <summary>
    /// 글꼴 컬렉션이 상대 경로로 로드될 때 사용할 기준 상대경로를 반환합니다.
    /// </summary>
    /// <returns>기준 상대경로 참조입니다.</returns>
    static std::filesystem::path& GetDefaultRelativeDirectory() { return AstrumFontsCacheSingleton::Instance().DefaultRelativeDirectory; }
    /// <summary>
    /// 글꼴 컬렉션이 상대 경로로 로드될 때 사용할 기준 상대경로를 설정합니다.
    /// </summary>
    /// <param name="path">설정할 기준 상대경로입니다.</param>
    static void SetDefaultRelativeDirectory(const std::filesystem::path& path) { AstrumFontsCacheSingleton::Instance().DefaultRelativeDirectory = path; }
    /// <summary>
    /// 글꼴 컬렉션이 상대 경로로 로드될 때 사용할 기준 상대경로를 설정합니다. (우측값 참조 버전)
    /// </summary>
    /// <param name="path">설정할 기준 상대경로입니다.</param>
    static void SetDefaultRelativeDirectory(std::filesystem::path&& path) { AstrumFontsCacheSingleton::Instance().DefaultRelativeDirectory = std::move(path); }
};

template<typename PathType>
requires std::same_as<std::remove_cvref_t<PathType>, std::filesystem::path>
inline std::shared_ptr<AstrumFonts> AstrumFontsCacheSingleton::Load(PathType&& path) {
    std::wstring name{
        std::forward<PathType>(path).is_absolute() ? std::forward<PathType>(path) : std::filesystem::canonical(DefaultRelativeDirectory / std::forward<PathType>(path))
    };
    if (!fontsMap.contains(name)) {
        fontsMap[name] = AstrumFonts::MakeShared(name);
    }
    return fontsMap[name];
}
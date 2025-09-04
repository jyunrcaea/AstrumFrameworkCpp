#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <filesystem>
#include "AstrumSingleton.hpp"
#include "../Resources/AstrumFonts.hpp"

class AstrumFontsCacheSingleton : public AstrumSingleton<AstrumFontsCacheSingleton>
{
	friend class AstrumSingleton<AstrumFontsCacheSingleton>;

public:
    template <typename PathType>
    requires std::same_as<std::remove_cvref_t<PathType>, std::filesystem::path>
    std::shared_ptr<AstrumFonts> Load(PathType&& path);
    void CleanUp();
    std::filesystem::path DefaultRelativeDirectory = L"./Game/Assets/";
private:
    std::unordered_map<std::wstring, std::weak_ptr<AstrumFonts>> fontsMap;
};

class AstrumFontsCache
{
    AstrumFontsCache() = delete;
public:
    // 주어진 경로의 글꼴 컬렉션을 로드합니다. 경로는 절대 경로 또는 상대 경로를 사용할 수 있습니다.
    static inline std::shared_ptr<AstrumFonts> Load(const std::filesystem::path& path) { return AstrumFontsCacheSingleton::Instance().Load(path); }
    static inline std::shared_ptr<AstrumFonts> Load(std::filesystem::path&& path) { return AstrumFontsCacheSingleton::Instance().Load(std::move(path)); }
    // 만료된 글꼴 컬렉션 참조를 모두 정리합니다.
    static inline void CleanUp() { AstrumFontsCacheSingleton::Instance().CleanUp(); }
    // 글꼴 컬렉션이 상대 경로로 로드될때 사용할 기준 상대경로를 반환합니다.
    static std::filesystem::path& GetDefaultRelativeDirectory() { return AstrumFontsCacheSingleton::Instance().DefaultRelativeDirectory; }
    // 글꼴 컬렉션이 상대 경로로 로드될때 사용할 기준 상대경로를 설정합니다.
    static void SetDefaultRelativeDirectory(const std::filesystem::path& path) { AstrumFontsCacheSingleton::Instance().DefaultRelativeDirectory = path; }
    static void SetDefaultRelativeDirectory(std::filesystem::path&& path) { AstrumFontsCacheSingleton::Instance().DefaultRelativeDirectory = std::move(path); }
};

template<typename PathType>
requires std::same_as<std::remove_cvref_t<PathType>, std::filesystem::path>
inline std::shared_ptr<AstrumFonts> AstrumFontsCacheSingleton::Load(PathType&& path) {
    std::wstring name{
        std::forward<PathType>(path).is_absolute() ? std::forward<PathType>(path) : std::filesystem::canonical(DefaultRelativeDirectory / std::forward<PathType>(path))
    };
    std::shared_ptr<AstrumFonts> fonts;
    if (fontsMap.contains(name) && (fonts = fontsMap[name].lock())) {
        return fonts;
    }
    fontsMap[name] = fonts = AstrumFonts::MakeShared(name);
    return fonts;
}
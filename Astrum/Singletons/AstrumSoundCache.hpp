#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <filesystem>
#include <cstdint>
#include "AstrumSingleton.hpp"
#include "../Resources/AstrumSound.hpp"

class AstrumSoundCacheSingleton : public AstrumSingleton<AstrumSoundCacheSingleton>
{
    friend class AstrumSingleton<AstrumSoundCacheSingleton>;
    friend class AstrumSoundCache;

public:
    template <typename PathType>
    requires std::same_as<std::remove_cvref_t<PathType>, std::filesystem::path>
    std::shared_ptr<AstrumSound> Load(PathType&& path, bool loop = false, std::shared_ptr<AstrumChannelGroup> group = nullptr);
    void CleanUp();
    std::filesystem::path DefaultRelativeDirectory = L"./Game/Assets/";
private:
    std::unordered_map<std::wstring, std::shared_ptr<AstrumSound>> soundMap;
};

class AstrumSoundCache {
    AstrumSoundCache() = delete;

public:
    static inline std::shared_ptr<AstrumSound> Load(const std::filesystem::path& path, bool loop = false, std::shared_ptr<AstrumChannelGroup> group = nullptr) { return AstrumSoundCacheSingleton::Instance().Load(path, loop, group); }
    static inline std::shared_ptr<AstrumSound> Load(std::filesystem::path&& path, bool loop = false, std::shared_ptr<AstrumChannelGroup> group = nullptr) { return AstrumSoundCacheSingleton::Instance().Load(std::move(path), loop, group); }
    static inline void CleanUp() { AstrumSoundCacheSingleton::Instance().CleanUp(); }

    static std::filesystem::path& GetDefaultRelativeDirectory() { return AstrumSoundCacheSingleton::Instance().DefaultRelativeDirectory; }
    static void SetDefaultRelativeDirectory(const std::filesystem::path& path) { AstrumSoundCacheSingleton::Instance().DefaultRelativeDirectory = path; }
    static void SetDefaultRelativeDirectory(std::filesystem::path&& path) { AstrumSoundCacheSingleton::Instance().DefaultRelativeDirectory = std::move(path); }
};

template<typename PathType>
requires std::same_as<std::remove_cvref_t<PathType>, std::filesystem::path>
inline std::shared_ptr<AstrumSound> AstrumSoundCacheSingleton::Load(PathType&& path, bool loop, std::shared_ptr<AstrumChannelGroup> group) {
    std::wstring baseName{
        std::forward<PathType>(path).is_absolute() ? std::forward<PathType>(path) : std::filesystem::canonical(DefaultRelativeDirectory / std::forward<PathType>(path))
    };

    // Include loop flag and group pointer in key to distinguish different sound instances when necessary.
    std::wstring key = baseName + L"|" + (loop ? L"1" : L"0") + L"|" + std::to_wstring(reinterpret_cast<std::uintptr_t>(group.get()));

    if (soundMap.contains(key)) {
        return soundMap[key];
    }

    return soundMap[key] = AstrumSound::MakeShared(baseName, loop, group);
}
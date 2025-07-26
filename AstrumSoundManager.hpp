#pragma once
#include <vector>
#include <memory>
#include <string>
#include "AstrumChannelGroup.hpp"
#include "FMOD/fmod.hpp"
#include "Singleton.hpp"

#pragma comment(lib, "./ThirdParty/fmod_vc.lib")

class AstrumSoundManagerSingleton : public Singleton<AstrumSoundManagerSingleton> {
    friend class Singleton<AstrumSoundManagerSingleton>;
    friend class AstrumSoundManager;

    struct FmodSystemDeleter {
        void operator()(FMOD::System* system) const {
            if (system) system->release();
        }
    };

public:
    void Initialize();
    void Update();
    void Dispose();

    void SetMasterChannelVolume(float volume) const;

    std::shared_ptr<AstrumChannelGroup> CreateChannelGroup(const std::string& name) const;
    std::shared_ptr<AstrumChannelGroup> GetMasterChannelGroup() const;
    FMOD::System* GetFmodSystem() const;
private:
    std::unique_ptr<FMOD::System, FmodSystemDeleter> system = nullptr;
    FMOD::ChannelGroup* masterChannelGroupPointer = nullptr;
    std::shared_ptr<AstrumChannelGroup> masterChannelGroup = nullptr;
};

class AstrumSoundManager {
public:
    static inline void Initialize() { AstrumSoundManagerSingleton::Instance().Initialize(); }
    static inline void Update() { AstrumSoundManagerSingleton::Instance().Update(); }
    static inline void Dispose() { AstrumSoundManagerSingleton::Instance().Dispose(); }

    static inline void SetMasterChannelVolume(float volume) { AstrumSoundManagerSingleton::Instance().SetMasterChannelVolume(volume); }
    static inline std::shared_ptr<AstrumChannelGroup> CreateChannelGroup(const std::string& name) { return AstrumSoundManagerSingleton::Instance().CreateChannelGroup(name); }
    static inline std::shared_ptr<AstrumChannelGroup> GetMasterChannelGroup() { return AstrumSoundManagerSingleton::Instance().GetMasterChannelGroup(); }
    static inline FMOD::System* GetFmodSystem() { return AstrumSoundManagerSingleton::Instance().GetFmodSystem(); }
};
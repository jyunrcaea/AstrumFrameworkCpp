#pragma once
#include "../FMOD/fmod.hpp"
#include <memory>

class AstrumChannelGroup {

    struct ChannelGroupDeleter {
        void operator()(FMOD::ChannelGroup* ptr) const {
            if (ptr) ptr->release();
        }
    };

public:
    explicit AstrumChannelGroup(FMOD::ChannelGroup* ptr);
    ~AstrumChannelGroup() = default;

    AstrumChannelGroup(const AstrumChannelGroup&) = delete;
    AstrumChannelGroup& operator=(const AstrumChannelGroup&) = delete;

    AstrumChannelGroup(AstrumChannelGroup&&) noexcept = default;
    AstrumChannelGroup& operator=(AstrumChannelGroup&&) noexcept = default;

    bool IsPlaying() const;
    void SetVolume(float volume) const;

    FMOD::ChannelGroup* GetFmodChannelGroup() const;

private:
    std::unique_ptr<FMOD::ChannelGroup, ChannelGroupDeleter> channelGroup;
};
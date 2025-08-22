#pragma once
#include "../FMOD/fmod.hpp"
#include <memory>

namespace Astrum
{
	class ChannelGroup {

		struct ChannelGroupDeleter {
			void operator()(FMOD::ChannelGroup* ptr) const {
				if (ptr) ptr->release();
			}
		};

	public:
		explicit ChannelGroup(FMOD::ChannelGroup* ptr);
		~ChannelGroup() = default;

		ChannelGroup(const ChannelGroup&) = delete;
		ChannelGroup& operator=(const ChannelGroup&) = delete;

		ChannelGroup(ChannelGroup&&) noexcept = default;
		ChannelGroup& operator=(ChannelGroup&&) noexcept = default;

		bool IsPlaying() const;
		void SetVolume(float volume) const;

		FMOD::ChannelGroup* GetFmodChannelGroup() const;

	private:
		std::unique_ptr<FMOD::ChannelGroup, ChannelGroupDeleter> channelGroup;
	};
}
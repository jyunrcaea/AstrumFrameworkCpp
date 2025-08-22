#pragma once
#include <memory>
#include <filesystem>
#include "../Singletons/AstrumSoundManager.hpp"

namespace Astrum
{
	class ChannelGroup;

	class Sound {

		struct FmodSoundDeleter {
			void operator()(FMOD::Sound* sound) const {
				if (sound) sound->release();
			}
		};

	public:
		Sound(const std::filesystem::path& soundFilePath, bool loop = false, std::shared_ptr<ChannelGroup> group = nullptr);
		~Sound();

		void Play();
		bool Stop();
		bool Pause();
		bool Resume();

		FMOD::Sound* GetFmodSound() const;
	private:
		std::unique_ptr<FMOD::Sound, FmodSoundDeleter> sound = nullptr;
		FMOD::Channel* channel = nullptr;
		std::shared_ptr<ChannelGroup> group;

		static FMOD_RESULT OnPlaySoundFinish(FMOD_CHANNELCONTROL* ChannelControl, FMOD_CHANNELCONTROL_TYPE type, FMOD_CHANNELCONTROL_CALLBACK_TYPE callBackType, void* commanddata1, void* commandData2);

	public:
		static inline std::filesystem::path DefaultRelativeDirectory = L"./";

		static std::shared_ptr<Sound> MakeShared(const std::filesystem::path& soundFilePath, bool loop = false, std::shared_ptr<ChannelGroup> group = nullptr) {
			return std::make_shared<Sound>(soundFilePath, loop, group);
		}
	};
}
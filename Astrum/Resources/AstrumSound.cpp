#include "AstrumSound.hpp"
#include <string>
#include "../AstrumException.hpp"

#if _DEBUG
#include <format>
#else
#include <iostream>
#endif

namespace
{
	void ThrowInitializeException(const char* message, int result) {
#if _DEBUG
		throw Astrum::Exception(__LINE__, __FILE__, std::format("{}. (FMOD_RESULT: {})", message, result));
#else
		std::cout << "[ERROR] " << message << ". (FMOD_RESULT: " << result << ")" << std::endl;
#endif
	}
}

namespace Astrum
{
	Sound::Sound(const std::filesystem::path& soundFilePath, bool loop, std::shared_ptr<ChannelGroup> group)
		: group(nullptr == group ? SoundManager::GetMasterChannelGroup() : group)
	{
		std::filesystem::path loadFrom;
		if (soundFilePath.is_absolute()) loadFrom = soundFilePath;
		else loadFrom = DefaultRelativeDirectory / soundFilePath;

		FMOD::Sound* soundPtr = nullptr;
		if (auto result = SoundManager::GetFmodSystem()->createSound(
			loadFrom.string().c_str(),
			loop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT,
			nullptr,
			&soundPtr
		)) ThrowInitializeException("Failed to load sound", result);

		sound.reset(soundPtr);
	}

	Sound::~Sound() {/* sound is managed by unique_ptr. */ }

	void Sound::Play()
	{
		SoundManager::GetFmodSystem()->playSound(sound.get(), group->GetFmodChannelGroup(), false, &channel);
		channel->setCallback(OnPlaySoundFinish);
	}

	bool Sound::Stop()
	{
		if (nullptr == channel) return false;

		bool playing;
		channel->isPlaying(&playing);
		if (false == playing) return false;

		channel->stop();
		channel = nullptr;

		return true;
	}

	bool Sound::Pause()
	{
		if (nullptr == channel) return false;

		bool playing;
		channel->isPlaying(&playing);
		if (false == playing) return false;

		channel->setPaused(true);

		return true;
	}

	bool Sound::Resume()
	{
		if (nullptr == channel) return false;

		bool paused;
		channel->getPaused(&paused);

		if (false == paused) return false;
		channel->setPaused(false);

		return true;
	}

	FMOD::Sound* Sound::GetFmodSound() const { return sound.get(); }

	FMOD_RESULT Sound::OnPlaySoundFinish(
		FMOD_CHANNELCONTROL*, //channelControl,
		FMOD_CHANNELCONTROL_TYPE, //type,
		FMOD_CHANNELCONTROL_CALLBACK_TYPE, //callBackType,
		void*, //commanddata1,
		void* //commandData2
	) {
		return FMOD_OK;
	}
}
#include "AstrumSound.hpp"
#include <string>
#include "AstrumException.hpp"

#if _DEBUG
#include <format>
#else
#include <iostream>
#endif

namespace {
	void ThrowInitializeException(const char* message, int result) {
#if _DEBUG
		throw AstrumException(__LINE__, __FILE__,std::format("{}. (FMOD_RESULT: {})", message, result));
#else
		std::cout << "[ERROR] " << message << ". (FMOD_RESULT: " << result << ")" << std::endl;
#endif
	}
}

AstrumSound::AstrumSound(const std::filesystem::path& soundFilePath, bool loop, std::shared_ptr<AstrumChannelGroup> group)
	: group(nullptr == group ? AstrumSoundManager::GetMasterChannelGroup() : group)
{
	std::filesystem::path loadFrom;
	if (soundFilePath.is_absolute()) loadFrom = soundFilePath;
	else loadFrom = DefaultRelativeDirectory / soundFilePath;

	FMOD::Sound* soundPtr = nullptr;
	if (auto result = AstrumSoundManager::GetFmodSystem()->createSound(
		loadFrom.string().c_str(),
		loop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT,
		nullptr,
		&soundPtr
	)) ThrowInitializeException("Failed to load sound", result);

	sound.reset(soundPtr);
}

AstrumSound::~AstrumSound()
{
	if (sound) {
		sound->release();
		sound = nullptr;
	}
}

void AstrumSound::Play()
{
	AstrumSoundManager::GetFmodSystem()->playSound(sound.get(), group->GetFmodChannelGroup(), false, &channel);
	channel->setCallback(OnPlaySoundFinish);
}

bool AstrumSound::Stop()
{
	if (nullptr == channel) return false;

	bool playing;
	channel->isPlaying(&playing);
	if (false == playing) return false;

	channel->stop();
	channel = nullptr;

	return true;
}

bool AstrumSound::Pause()
{
	if (nullptr == channel) return false;

	bool playing;
	channel->isPlaying(&playing);
	if (false == playing) return false;

	channel->setPaused(true);

	return true;
}

bool AstrumSound::Resume()
{
	if (nullptr == channel) return false;

	bool paused;
	channel->getPaused(&paused);

	if (false == paused) return false;
	channel->setPaused(false);

	return true;
}

FMOD::Sound* AstrumSound::GetFmodSound() const { return sound.get(); }

FMOD_RESULT AstrumSound::OnPlaySoundFinish(FMOD_CHANNELCONTROL* ChannelControl, FMOD_CHANNELCONTROL_TYPE type, FMOD_CHANNELCONTROL_CALLBACK_TYPE callBackType, void* commanddata1, void* commandData2)
{
	return FMOD_OK;
}
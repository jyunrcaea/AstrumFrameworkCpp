#include "AstrumSoundManager.hpp"
#include <string>
#include "../AstrumException.hpp"

#if _DEBUG
#include <format>
#else
#include <iostream>
#endif

namespace Astrum {
	namespace {
		void ThrowInitalizeException(const char* message, int result) {
	#if _DEBUG
			throw AstrumException(__LINE__, __FILE__, std::format("{}. (FMOD_RESULT: {})", message, result));
	#else
			std::cout << "[ERROR] " << message << ". (FMOD_RESULT: " << result << ")" << std::endl;
	#endif
		}
	}

	SoundManagerSingleton::SoundManagerSingleton() { }

	void SoundManagerSingleton::Initialize() {
		FMOD_RESULT result;
		auto throwException = [result](const char* message) { ThrowInitalizeException(message, result); };

		if (FMOD::System* systemPtr = nullptr; (result = FMOD::System_Create(&systemPtr)) != FMOD_RESULT::FMOD_OK) {
			throwException("Failed to create fmod system");
			return;
		}
		else system.reset(systemPtr);

		if ((result = system->init(256, FMOD_INIT_NORMAL, nullptr)) != FMOD_RESULT::FMOD_OK) {
			throwException("Failed to initialize fmod system");
			return;
		}

		if ((result = system->getMasterChannelGroup(&masterChannelGroupPointer)) != FMOD_RESULT::FMOD_OK) {
			throwException("Failed to get master channel group");
			return;
		}

		masterChannelGroup = std::make_shared<ChannelGroup>(masterChannelGroupPointer);
	}

	void SoundManagerSingleton::Update() {
		system->update();
	}

	void SoundManagerSingleton::Dispose() {
		masterChannelGroup.reset();

		if (system) {
			system->close();
			system->release();
			system = nullptr;
		}
	}

	void SoundManagerSingleton::SetMasterChannelVolume(float volume) const
	{
		masterChannelGroup->SetVolume(volume);
	}

	std::shared_ptr<ChannelGroup> SoundManagerSingleton::CreateChannelGroup(const std::string& name) const
	{
		FMOD::ChannelGroup* group;

		if (auto result = system->createChannelGroup(name.c_str(), &group)) {
			ThrowInitalizeException("Failed to create channel group", result);
			return nullptr;
		}

		masterChannelGroupPointer->addGroup(group);
		return std::make_shared<ChannelGroup>(group);
	}

	std::shared_ptr<ChannelGroup> SoundManagerSingleton::GetMasterChannelGroup() const { return masterChannelGroup; }
	FMOD::System* SoundManagerSingleton::GetFmodSystem() const { return system.get(); }
}
#include "AstrumSoundManager.hpp"
#include <string>
#include <format>
#include "../AstrumException.hpp"

#define ThrowInitalizeException(message, result) AstrumException(__LINE__, __FILE__, std::format("{} (FMOD_RESULT: {})", message, static_cast<int>(result))).Alert();

AstrumSoundManagerSingleton::AstrumSoundManagerSingleton() { }

void AstrumSoundManagerSingleton::Initialize() {
	FMOD_RESULT result;
	auto throwException = [result](std::string&& message) { ThrowInitalizeException(message, result); };

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
	
	masterChannelGroup = std::make_shared<AstrumChannelGroup>(masterChannelGroupPointer);
}

void AstrumSoundManagerSingleton::Update() {
	system->update();
}

void AstrumSoundManagerSingleton::Dispose() {
	masterChannelGroup.reset();

	if (system) {
		system->close();
		system->release();
		system = nullptr;
	}
}

void AstrumSoundManagerSingleton::SetMasterChannelVolume(float volume) const
{
	masterChannelGroup->SetVolume(volume);
}

std::shared_ptr<AstrumChannelGroup> AstrumSoundManagerSingleton::CreateChannelGroup(const std::string& name) const
{
	FMOD::ChannelGroup* group;

	if (auto result = system->createChannelGroup(name.c_str(), &group)) {
		ThrowInitalizeException("Failed to create channel group", result);
		return nullptr;
	}

	masterChannelGroupPointer->addGroup(group);
	return std::make_shared<AstrumChannelGroup>(group);
}

std::shared_ptr<AstrumChannelGroup> AstrumSoundManagerSingleton::GetMasterChannelGroup() const { return masterChannelGroup; }
FMOD::System* AstrumSoundManagerSingleton::GetFmodSystem() const { return system.get(); }
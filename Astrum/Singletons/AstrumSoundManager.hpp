#pragma once
#include <vector>
#include <memory>
#include <string>
#include "../Resources/AstrumChannelGroup.hpp"
#include "../FMOD/fmod.hpp"
#include "AstrumSingleton.hpp"

#pragma comment(lib, "Astrum/ThirdParty/fmod_vc.lib")

namespace Astrum {
	class SoundManager;

	class SoundManagerSingleton : public Singleton<SoundManagerSingleton> {
		friend class Singleton<SoundManagerSingleton>;
		friend class SoundManager;
		SoundManagerSingleton();

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

		std::shared_ptr<ChannelGroup> CreateChannelGroup(const std::string& name) const;
		std::shared_ptr<ChannelGroup> GetMasterChannelGroup() const;
		FMOD::System* GetFmodSystem() const;

	private:
		std::unique_ptr<FMOD::System, FmodSystemDeleter> system = nullptr;
		FMOD::ChannelGroup* masterChannelGroupPointer = nullptr;
		std::shared_ptr<ChannelGroup> masterChannelGroup = nullptr;
	};

	class SoundManager {
		SoundManager() = delete;
	public:
		static inline void Initialize() { SoundManagerSingleton::Instance().Initialize(); }
		static inline void Update() { SoundManagerSingleton::Instance().Update(); }
		static inline void Dispose() { SoundManagerSingleton::Instance().Dispose(); }

		static inline void SetMasterChannelVolume(float volume) { SoundManagerSingleton::Instance().SetMasterChannelVolume(volume); }
		static inline std::shared_ptr<ChannelGroup> CreateChannelGroup(const std::string& name) { return SoundManagerSingleton::Instance().CreateChannelGroup(name); }
		static inline std::shared_ptr<ChannelGroup> GetMasterChannelGroup() { return SoundManagerSingleton::Instance().GetMasterChannelGroup(); }
		static inline FMOD::System* GetFmodSystem() { return SoundManagerSingleton::Instance().GetFmodSystem(); }
	};
}
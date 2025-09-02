#pragma once
#include "../../Astrum/Singletons/AstrumSingleton.hpp"
#include "ArcaeaMusicData.hpp"

namespace Arcaea {
	class MusicDataManagerSingleton : public AstrumSingleton<MusicDataManagerSingleton>
	{
		friend class AstrumSingleton<MusicDataManagerSingleton>;
		friend class MusicDataManager;

	private:
		MusicDataManagerSingleton() {
			for (const auto& entry : std::filesystem::directory_iterator(FolderPath)) {
				if (false == entry.is_directory()) continue;

				if (auto path = entry.path();  std::filesystem::exists(path / L"base.ogg")) {
					musics.emplace_back(std::move(path));
				}
			}
		}

		const std::vector<MusicData>& GetMusics() { return musics; }

	private:
		std::vector<MusicData> musics;

	public:
		inline static std::filesystem::path FolderPath = L"Game/Assets/songs";
	};

	class MusicDataManager
	{
		MusicDataManager() = delete;
	public:
		static const std::vector<MusicData>& GetMusics() { return MusicDataManagerSingleton::Instance().GetMusics(); }
	};
}
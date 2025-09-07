#pragma once
#include <memory>
#include "../../Astrum/Singletons/AstrumSingleton.hpp"
#include "../Arcaea/ArcaeaMusicData.hpp"

namespace Selector {
	class MusicBarObject;

	class DataManager : public AstrumSingleton<DataManager>
	{
		friend class AstrumSingleton<DataManager>;

	public:
		MusicBarObject* CurrentSelectedMusicBar = nullptr;
		const Arcaea::MusicData* GetCurrentSelectedMusic();

	private:
	};
}
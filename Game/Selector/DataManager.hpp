#pragma once
#include <memory>
#include "../../Astrum/Singletons/AstrumSingleton.hpp"
#include "../Arcaea/ArcaeaMusicData.hpp"

namespace Selector {
	class DataManager : public AstrumSingleton<DataManager>
	{
		friend class DataManager;

	public:
		
		inline static Arcaea::MusicData* CurrentSelectedMusic = nullptr;
	private:
	};
}
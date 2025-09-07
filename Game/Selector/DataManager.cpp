#include "DataManager.hpp"
#include "MusicBarObject.hpp"

namespace  Selector {
	const Arcaea::MusicData* DataManager::GetCurrentSelectedMusic()
	{
		if (nullptr == CurrentSelectedMusicBar) return nullptr;
		return CurrentSelectedMusicBar->GetMusicData();
	}
}
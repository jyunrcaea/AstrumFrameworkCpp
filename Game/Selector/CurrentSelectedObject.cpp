#include "CurrentSelectedObject.hpp"
#include "../../Astrum/Singletons/AstrumTextureCache.hpp"
#include "MusicBarObject.hpp"

namespace Selector {
	CurrentSelectedObject::CurrentSelectedObject()
		: AstrumMaterialObject(AstrumTextureCache::Load("songselect/song_cell_selected_piece.png")) {

	}

	void CurrentSelectedObject::Update() {
		if (MusicBarObject* musicBar = DataManager::Instance().CurrentSelectedMusicBar) {
			SetVisible(true);
			SetPositionY(musicBar->GetAbsolutePosition().Y);
		}
		else {
			SetVisible(false);
		}

		AstrumMaterialObject::Update();
	}
}
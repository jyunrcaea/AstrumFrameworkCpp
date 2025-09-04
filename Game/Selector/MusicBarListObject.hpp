#pragma once
#include <vector>
#include "../../Astrum/Objects/AstrumGroupObject.hpp"
#include "../Arcaea/ArcaeaMusicDataManager.hpp"
#include "MusicBarObject.hpp"

namespace Selector {
	class MusicBarListObject : public AstrumGroupObject
	{
	public:
		MusicBarListObject() {
			SetPositionZ(100);
			float offsetY = 0;
			const float paddingY = static_cast<float>(AstrumTextureCache::Load("songselect/song_cell_right_world.png")->GetHeight());
			for (const auto& data : Arcaea::MusicDataManager::GetMusics()) {
				auto child = std::make_shared<MusicBarObject>(data);
				AddObject(child);
				child->SetPositionY(offsetY);
				offsetY += paddingY;
			}
		}

	private:
	};
}
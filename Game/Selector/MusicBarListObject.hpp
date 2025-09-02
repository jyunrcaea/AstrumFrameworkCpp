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
			float offsetY = 0;
			for (const auto& data : Arcaea::MusicDataManager::GetMusics()) {
				auto child = std::make_shared<MusicBarObject>();
				AddObject(child);
				child->SetPositionY(offsetY);
				offsetY += child->GetTexture()->GetHeight();
			}
		}

	private:
	};
}
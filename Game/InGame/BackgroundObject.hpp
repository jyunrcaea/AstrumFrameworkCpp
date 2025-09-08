#pragma once
#include "DataManager.hpp"
#include "../../Astrum/Objects/AstrumMaterialObject.hpp"
#include "../../Astrum/Singletons/AstrumTextureCache.hpp"

namespace InGame {
	class BackgroundObject : public AstrumMaterialObject
	{
	public:
		BackgroundObject()
			: AstrumMaterialObject(AstrumTextureCache::Load("background.png")) {

			float fillScale = (std::max)(
				static_cast<float>(AstrumWindow::GetWidth()) / static_cast<float>(GetTextureWidth()),
				static_cast<float>(AstrumWindow::GetHeight()) / static_cast<float>(GetTextureHeight())
			);
		}
	};
}
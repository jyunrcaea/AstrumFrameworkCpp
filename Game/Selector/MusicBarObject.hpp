#pragma once
#include "../../Astrum/Objects/AstrumGroupObject.hpp"
#include "../../Astrum/Objects/AstrumMaterialObject.hpp"
#include "../../Astrum/Objects/AstrumTextObject.hpp"
#include "../../Astrum/Singletons/AstrumTextureCache.hpp"
#include "../../Astrum/Singletons/AstrumFontsCache.hpp"
#include "../Arcaea/ArcaeaMusicData.hpp"

namespace Selector
{
	class MusicBarObject : public AstrumGroupObject {
	public:
		MusicBarObject(const Arcaea::MusicData& music) {
			//SetScale({ 0.5f, 0.5f, 1.f });

			AddObject(backgroundObject = AstrumMaterialObject::MakeShared(
				barMaterial,
				barMaterial->CreateTextureSizeMesh()
			));
			backgroundObject->SetPositionZ(-1);

			AddObject(titleObject = AstrumTextObject::MakeShared(
				music.GetName(),
				AstrumFontsCache::Load(L"Outfit-Regular.ttf")->GetFont(music.GetName(), 48.f)
			));
			titleObject->SetAlignment(AstrumTextHorizontalAlignmentType_Center, AstrumTextVerticalAlignmentType_Center);
			titleObject->SetPositionZ(1);
		}

	private:
		std::shared_ptr<AstrumMaterialObject> backgroundObject;
		std::shared_ptr<AstrumMaterial> barMaterial = AstrumMaterial::MakeShared(AstrumTextureCache::Load("songselect/song_cell_right_world.png"));
		std::shared_ptr<AstrumMaterial> barSelectedMaterial = AstrumMaterial::MakeShared(AstrumTextureCache::Load("songselect/song_cell_right_world_selected.png"));

		std::shared_ptr<AstrumTextObject> titleObject;
	};
}
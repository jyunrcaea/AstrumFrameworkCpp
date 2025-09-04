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
		MusicBarObject(const std::unique_ptr<Arcaea::MusicData>& music) {
			AddObject(thumbnailObject = AstrumMaterialObject::MakeShared(
				AstrumMaterial::MakeShared(music->GetThumbnailTexture())
			));
			thumbnailObject->SetTextureMesh(thumbnailObject->GetMaterial()->CreateTextureSizeMesh());

			AddObject(backgroundObject = AstrumMaterialObject::MakeShared(
				barMaterial,
				barMaterial->CreateTextureSizeMesh()
			));
			backgroundObject->SetPositionZ(0);

			AddObject(titleObject = AstrumTextObject::MakeShared(
				music->GetName(),
				AstrumFontsCache::Load(L"Outfit-Regular.ttf")->GetFont(music->GetName(), 32.f)
			));
			titleObject->SetAlignment(AstrumTextHorizontalAlignmentType_Center, AstrumTextVerticalAlignmentType_Center);
			titleObject->SetPositionZ(1);
		}

	private:
		std::shared_ptr<AstrumMaterialObject> thumbnailObject;

		std::shared_ptr<AstrumMaterialObject> backgroundObject;
		std::shared_ptr<AstrumMaterial> barMaterial = AstrumMaterial::MakeShared(AstrumTextureCache::Load("songselect/song_cell_right_world.png"));
		std::shared_ptr<AstrumMaterial> barSelectedMaterial = AstrumMaterial::MakeShared(AstrumTextureCache::Load("songselect/song_cell_right_world_selected.png"));

		std::shared_ptr<AstrumTextObject> titleObject;
	};
}
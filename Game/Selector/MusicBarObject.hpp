#pragma once
#include "../../Astrum/Objects/AstrumGroupObject.hpp"
#include "../../Astrum/Objects/AstrumMaterialObject.hpp"
#include "../../Astrum/Singletons/AstrumTextureCache.hpp"

namespace Selector
{
	class MusicBarObject : public AstrumGroupObject {
	public:
		MusicBarObject() {
			barMaterial = AstrumMaterial::MakeShared(AstrumTextureCache::Load("songselect/song_cell_right_world.png"));
			barSelectedMaterial = AstrumMaterial::MakeShared(AstrumTextureCache::Load("songselect/song_cell_right_world_selected.png"));

			AddObjects({
				(barObject = AstrumMaterialObject::MakeShared(barMaterial, barMaterial->CreateTextureSizeMesh()))
			});
		}

	private:
		std::shared_ptr<AstrumMaterialObject> barObject;
		std::shared_ptr<AstrumMaterial> barMaterial;
		std::shared_ptr<AstrumMaterial> barSelectedMaterial;
		
	};
}
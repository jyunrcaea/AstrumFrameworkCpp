#pragma once
#include "DataManager.hpp"
#include "../../Astrum/Objects/AstrumGroupObject.hpp"
#include "../../Astrum/Objects/AstrumMaterialObject.hpp"
#include "../../Astrum/Objects/AstrumTextObject.hpp"
#include "../../Astrum/Singletons/AstrumTextureCache.hpp"
#include "../../Astrum/Singletons/AstrumFontsCache.hpp"
#include "../../Astrum/Components/AstrumAABBColliderComponent.hpp"
#include "../../Astrum/Singletons/AstrumRawInput.hpp"
#include "../Arcaea/ArcaeaMusicData.hpp"

namespace Selector
{
	constexpr float MusicBarTitleObjectFontSize = 28.f;
	constexpr float MusicBarObjectClickableBackgroundAreaScale = 0.82f;

	class MusicBarObject : public AstrumGroupObject {
	public:
		MusicBarObject(const std::unique_ptr<Arcaea::MusicData>& music);

		virtual void Update() override;

		const Arcaea::MusicData* GetMusicData() { return &musicData; }
	private:
		const Arcaea::MusicData& musicData;

		std::shared_ptr<AstrumMaterialObject> thumbnailObject;

		std::shared_ptr<AstrumMaterialObject> backgroundObject;
		std::shared_ptr<AstrumMaterial> barMaterial = AstrumMaterial::MakeShared(AstrumTextureCache::Load("songselect/song_cell_right_world.png"));
		std::shared_ptr<AstrumMaterial> barSelectedMaterial = AstrumMaterial::MakeShared(AstrumTextureCache::Load("songselect/song_cell_right_world_selected.png"));
		std::shared_ptr<AstrumAABBColliderComponent> backgroundAABB = AstrumAABBColliderComponent::MakeShared();

		std::shared_ptr<AstrumTextObject> titleObject;
	};
}
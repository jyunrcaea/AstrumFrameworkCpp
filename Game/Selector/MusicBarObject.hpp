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
		MusicBarObject(const std::unique_ptr<Arcaea::MusicData>& music) : musicData(*music) {
			AddObject(thumbnailObject = AstrumMaterialObject::MakeShared(
				AstrumMaterial::MakeShared(music->GetThumbnailTexture())
			));
			thumbnailObject->SetTextureMesh(thumbnailObject->GetMaterial()->CreateCustomSizeMeshFromRatio(0, 0.3f, 1, 0.7f));
			thumbnailObject->SetPositionZ(0.5f);

			AddObject(backgroundObject = AstrumMaterialObject::MakeShared(
				barMaterial,
				barMaterial->CreateTextureSizeMesh()
			));
			backgroundObject->SetPositionZ(0);
			backgroundObject->AddComponent(backgroundAABB);

			AddObject(titleObject = AstrumTextObject::MakeShared(
				music->GetName(),
				AstrumFontsCache::Load(L"Outfit-Regular.ttf")->GetFont(music->GetName(), MusicBarTitleObjectFontSize)
			));
			titleObject->SetAlignment(AstrumTextHorizontalAlignmentType_Left, AstrumTextVerticalAlignmentType_Top);
			titleObject->SetPositionZ(-0.5f);
			titleObject->SetColor(AstrumColor::White);

			const float thumbnailScale = static_cast<float>(backgroundObject->GetTextureHeight()) / static_cast<float>(thumbnailObject->GetTextureHeight() * 0.4) * MusicBarObjectClickableBackgroundAreaScale;
			thumbnailObject->SetScale({ thumbnailScale, thumbnailScale, 1.f });
			thumbnailObject->SetPositionX(static_cast<float>(-0.5 * backgroundObject->GetTextureWidth() + 0.5 * thumbnailObject->GetTextureWidth() * thumbnailScale));

			titleObject->SetPositionY(static_cast<float>(-0.5 * backgroundObject->GetTextureHeight() + 0.75 * MusicBarTitleObjectFontSize));
			titleObject->SetPositionX(static_cast<float>(-0.5 * backgroundObject->GetTextureWidth() + 0.6 * titleObject->GetLayoutWidth()));

			backgroundAABB->GetRectFunction = [this]() {
				AstrumVector2 leftTop{ static_cast<float>(backgroundObject->GetTextureWidth()), static_cast<float>(backgroundObject->GetTextureHeight()) };
				leftTop *= -0.5f;
				leftTop *= MusicBarObjectClickableBackgroundAreaScale;
				AstrumVector2 rightBottom = leftTop * -1.f;

				leftTop.X += this->GetAbsolutePosition().X;
				leftTop.Y += this->GetAbsolutePosition().Y;

				rightBottom.X += this->GetAbsolutePosition().X;
				rightBottom.Y += this->GetAbsolutePosition().Y;

				return AstrumRect(leftTop,rightBottom);
			};
		}

		virtual void Update() override {
			if (AstrumRawInput::WasMousePressed() && backgroundAABB->IsOverlapToMousePointer()) {
				DataManager::CurrentSelectedMusic = &musicData;
				std::wcout << L"Selected music: " << musicData.GetName() << std::endl;
			}

			AstrumGroupObject::Update();
		}

	private:
		Arcaea::MusicData& musicData;

		std::shared_ptr<AstrumMaterialObject> thumbnailObject;

		std::shared_ptr<AstrumMaterialObject> backgroundObject;
		std::shared_ptr<AstrumMaterial> barMaterial = AstrumMaterial::MakeShared(AstrumTextureCache::Load("songselect/song_cell_right_world.png"));
		std::shared_ptr<AstrumMaterial> barSelectedMaterial = AstrumMaterial::MakeShared(AstrumTextureCache::Load("songselect/song_cell_right_world_selected.png"));
		std::shared_ptr<AstrumAABBColliderComponent> backgroundAABB = AstrumAABBColliderComponent::MakeShared();

		std::shared_ptr<AstrumTextObject> titleObject;
	};
}
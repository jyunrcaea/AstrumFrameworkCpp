#include "MusicBarObject.hpp"
#include "../SceneManager.hpp"
#include "../../Astrum/Singletons/AstrumFramework.hpp"

Selector::MusicBarObject::MusicBarObject(const std::unique_ptr<Arcaea::MusicData>& music)
	: musicData(*music) {
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

		return AstrumRect(leftTop, rightBottom);
	};
}

void Selector::MusicBarObject::Update()
{
	if (AstrumRawInput::IsMouseClickNow() && backgroundAABB->IsOverlapToMousePointer()) {
		if (this == DataManager::Instance().CurrentSelectedMusicBar) {
			InGame::DataManager::Instance().CurrentMusic = &musicData;
			Game::SceneManager::LoadingScene->LoadScene([](auto*) {
				const auto& root = AstrumFramework::GetRootObject();
				root->AddObject(std::make_shared<InGame::SceneObject>());
				root->RemoveObject(Game::SceneManager::SelectorScene->shared_from_this());
			});
		}
		else DataManager::Instance().CurrentSelectedMusicBar = this;
	}

	// Update material by selected state.
	if (this == DataManager::Instance().CurrentSelectedMusicBar) {
		if (backgroundObject->GetMaterial() != barSelectedMaterial) backgroundObject->SetMaterial(barSelectedMaterial);
	}
	else {
		if (backgroundObject->GetMaterial() != barMaterial) backgroundObject->SetMaterial(barMaterial);
	}

	AstrumGroupObject::Update();
}
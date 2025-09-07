#pragma once
#include <cmath>
#include <algorithm>
#include "../../Astrum/Objects/AstrumMaterialObject.hpp"
#include "../../Astrum/Singletons/AstrumChrono.hpp"
#include "DataManager.hpp"

namespace Selector {
	class MusicThumbnailObject : public AstrumMaterialObject
	{
	public:
		MusicThumbnailObject() {
			SetScale({ 0.8f, 0.8f, 1.0f });
		}

		virtual void Update() override {
			if (auto rotated = GetRotation().GetZ(); rotated < 30) {
				rotated = (std::max)(-5.f, static_cast<float>(rotated + AstrumChrono::GetDeltaTime() * -45.f));
				SetRotationZ(rotated);
			}

			if (auto now = DataManager::Instance().GetCurrentSelectedMusic(); appearMusic != now) {
				appearMusic = now;
				SetMaterial(AstrumMaterial::MakeShared(appearMusic->GetThumbnailTexture()));
				SetTextureMesh(GetMaterial()->CreateTextureSizeMesh());
				SetRotationZ(0);
			}

			AstrumMaterialObject::Update();
		}

	private:
		const Arcaea::MusicData* appearMusic = nullptr;
	};
}
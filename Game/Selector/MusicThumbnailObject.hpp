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

		}

		virtual void Update() override {
			if (auto rotated = GetRotation().GetZ(); rotated < 30) {
				rotated = (std::max)(30.f, static_cast<float>(rotated + AstrumChrono::GetDeltaTime() * 60));
			}

			if (auto now = DataManager::Instance().CurrentSelectedMusic; appearMusic != now) {
				appearMusic = now;
				SetMaterial(AstrumMaterial::MakeShared(appearMusic->GetThumbnailTexture()));
				SetRotationZ(0);
			}

			AstrumMaterialObject::Update();
		}

	private:
		Arcaea::MusicData* appearMusic = nullptr;
	};
}
#pragma once
#include "DataManager.hpp"
#include "../../Astrum/Objects/AstrumMaterialObject.hpp"
#include "../../Astrum/Components/AstrumFrameAnimationComponent.hpp"
#include "../../Astrum/Singletons/AstrumTextureCache.hpp"

namespace InGame {
	class ParticleObject : public AstrumMaterialObject
	{
	public:
		ParticleObject() {
			std::vector<std::shared_ptr<AstrumMaterial>> keyframes;
			keyframes.reserve(10);
			for (int i = 1; i <= 10; i++) {
				keyframes.emplace_back(AstrumMaterial::MakeShared(
					AstrumTextureCache::Load(std::format(L"sky{}.png", i))
				));
			}

			AddComponent(
				keyframeComponent = AstrumFrameAnimationComponent::MakeShared(std::move(keyframes))
			);
		}

	private:
		std::shared_ptr<AstrumFrameAnimationComponent> keyframeComponent = nullptr;
	};
}
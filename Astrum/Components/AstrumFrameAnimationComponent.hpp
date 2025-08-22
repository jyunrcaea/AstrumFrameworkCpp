#pragma once
#include "AstrumComponent.hpp"
#include "../Objects/IAstrumMaterialObject.hpp"
#include "IAstrumFrameAnimationComponent.hpp"

namespace Astrum {
	class FrameAnimationComponent : public Component, public IFrameAnimationComponent
	{
	public:
		virtual void Update() override;
		virtual void SetOwner(IObject* owner) override;

		// 프레임이 변경될때마다 호출될 콜백
		std::function<void(unsigned short)> OnFrameChanged = nullptr;

		// 현재 프레임 (0번부터 시작, 프레임수와 같을 경우 재생이 끝남을 의미)
		unsigned short FrameIndex = 0;
		// 반복 여부
		bool Loop = true;
		// 반대로 재생할지에 대한 여부
		bool Reverse = false;

		// 한 프레임당 가질 시간 (초 단위)
		float TimePerFrame = 1.f;
		// 재생 속도 (기본값은 1.0f)
		float PlaybackSpeed = 1.f;

		std::vector<std::shared_ptr<Material>>& GetFrames();
		IMaterialObject* GetMaterialObjectOwner() const;

	private:
		float sumTime = 0;
		std::vector<std::shared_ptr<Material>> frames;
		IMaterialObject* materialOwner = nullptr;

	public:
		static std::shared_ptr<FrameAnimationComponent> MakeShared() {
			return std::make_shared<FrameAnimationComponent>();
		}
		static std::shared_ptr<FrameAnimationComponent> MakeShared(const std::vector<std::shared_ptr<Material>>& frames) {
			auto component = std::make_shared<FrameAnimationComponent>();
			component->frames = frames;
			return component;
		}
	};
}
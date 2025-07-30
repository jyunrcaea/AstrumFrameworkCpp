#pragma once
#include "AstrumComponent.hpp"
#include "../Objects/IAstrumMaterialObject.hpp"
#include "IAstrumFrameAnimationComponent.hpp"

class AstrumFrameAnimationComponent : public AstrumComponent, public IAstrumFrameAnimationComponent
{
public:
	virtual void Update() override;
	virtual void SetOwner(IAstrumObject* owner) override;

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

	std::vector<std::shared_ptr<AstrumMaterial>>& GetFrames();
	IAstrumMaterialObject* GetMaterialObjectOwner() const;

private:
	float sumTime = 0;
	std::vector<std::shared_ptr<AstrumMaterial>> frames;
	IAstrumMaterialObject* materialOwner = nullptr;

public:
	static std::shared_ptr<AstrumFrameAnimationComponent> MakeShared() {
		return std::make_shared<AstrumFrameAnimationComponent>();
	}
	static std::shared_ptr<AstrumFrameAnimationComponent> MakeShared(const std::vector<std::shared_ptr<AstrumMaterial>>& frames) {
		auto component = std::make_shared<AstrumFrameAnimationComponent>();
		component->frames = frames;
		return component;
	}
};
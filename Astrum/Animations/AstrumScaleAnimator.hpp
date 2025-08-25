#pragma once
#include "AstrumAnimator.hpp"

struct AstrumScaleAnimator : public AstrumAnimator {
public:
	AstrumScaleAnimator(const AstrumVector3& targetScale, float animationTime) : next(targetScale), AstrumAnimator(animationTime) {}
	AstrumScaleAnimator(float animationTime, float targetX = NAN, float targetY = NAN, float targetZ = NAN) : next(targetX, targetY, targetZ), AstrumAnimator(animationTime) {}

	virtual void Prepare() override {
		previous = owner->GetScale();
	}
protected:
	virtual void Apply(double percent) override {
		if (false == std::isnan(next.X)) {
			owner->GetScale().SetX(static_cast<float>(std::lerp(previous.X, next.X, percent)));
		}
		if (false == std::isnan(next.Y)) {
			owner->GetScale().SetY(static_cast<float>(std::lerp(previous.Y, next.Y, percent)));
		}
		if (false == std::isnan(next.Z)) {
			owner->GetScale().SetZ(static_cast<float>(std::lerp(previous.Z, next.Z, percent)));
		}
	}

private:
	AstrumVector3 previous{};
	AstrumVector3 next{};

public:
	// float 값이 NaN일경우 해당 좌표 축은 업데이트 하지 않습니다.
	static std::shared_ptr<AstrumScaleAnimator> MakeShared(const AstrumVector3& targetScale, float animationTime) {
		return std::make_shared<AstrumScaleAnimator>(targetScale, animationTime);
	}
	// float 값이 NaN일경우 해당 좌표 축은 업데이트 하지 않습니다.
	static std::shared_ptr<AstrumScaleAnimator> MakeShared(float animationTime, float targetX = NAN, float targetY = NAN, float targetZ = NAN) {
		return std::make_shared<AstrumScaleAnimator>(animationTime, targetX, targetY, targetZ);
	}
};
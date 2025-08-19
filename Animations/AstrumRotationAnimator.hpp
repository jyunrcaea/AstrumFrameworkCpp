#pragma once
#include "AstrumAnimator.hpp"

struct AstrumRotationAnimator : public AstrumAnimator {
public:
	AstrumRotationAnimator(const AstrumVector3& targetRotation, float animationTime) : next(targetRotation), AstrumAnimator(animationTime) {}
	AstrumRotationAnimator(float animationTime, float targetX = NAN, float targetY = NAN, float targetZ = NAN) : next(targetX, targetY, targetZ), AstrumAnimator(animationTime) {}

	virtual void Prepare() override {
		previous = owner->GetRotation();
	}
protected:
	virtual void Apply(double percent) override {
		if (false == std::isnan(next.X)) {
			owner->GetRotation().SetX(static_cast<float>(std::lerp(previous.X, next.X, percent)));
		}
		if (false == std::isnan(next.Y)) {
			owner->GetRotation().SetY(static_cast<float>(std::lerp(previous.Y, next.Y, percent)));
		}
		if (false == std::isnan(next.Z)) {
			owner->GetRotation().SetZ(static_cast<float>(std::lerp(previous.Z, next.Z, percent)));
		}
	}

private:
	AstrumVector3 previous{};
	AstrumVector3 next{};

public:
	// float 값이 NaN일경우 해당 좌표 축은 업데이트 하지 않습니다.
	static std::shared_ptr<AstrumRotationAnimator> MakeShared(const AstrumVector3& targetRotation, float animationTime) {
		return std::make_shared<AstrumRotationAnimator>(targetRotation, animationTime);
	}
	// float 값이 NaN일경우 해당 좌표 축은 업데이트 하지 않습니다.
	static std::shared_ptr<AstrumRotationAnimator> MakeShared(float animationTime, float targetX = NAN, float targetY = NAN, float targetZ = NAN) {
		return std::make_shared<AstrumRotationAnimator>(animationTime, targetX, targetY, targetZ);
	}
};
#pragma once
#include <cmath>
#include "AstrumAnimator.hpp"

struct AstrumMovementAnimator :  public AstrumAnimator {
public:
	// float 값이 NaN일경우 해당 좌표 축은 업데이트 하지 않습니다.
	AstrumMovementAnimator(const AstrumVector3& targetPosition, float animationTime) : next(targetPosition), AstrumAnimator(animationTime) {}
	AstrumMovementAnimator(float animationTime, float targetX = NAN, float targetY = NAN, float targetZ = NAN) : next(targetX, targetY, targetZ), AstrumAnimator(animationTime) {}

	virtual void Prepare() override {
		previous = owner->GetPosition();
	}
protected:
	virtual void Apply(double percent) override {
		if (false == std::isnan(next.X)) {
			owner->GetPosition().SetX(std::lerp(previous.X, next.X, percent));
		}
		if (false == std::isnan(next.Y)) {
			owner->GetPosition().SetY(std::lerp(previous.Y, next.Y, percent));
		}
		if (false == std::isnan(next.Z)) {
			owner->GetPosition().SetZ(std::lerp(previous.Z, next.Z, percent));
		}
	}
	
private:
	AstrumVector3 previous{};
	AstrumVector3 next{};

public:
	static std::shared_ptr<AstrumMovementAnimator> MakeShared(const AstrumVector3& targetPosition, float animationTime = 1.f) {
		return std::make_shared<AstrumMovementAnimator>(targetPosition, animationTime);
	}
	static std::shared_ptr<AstrumMovementAnimator> MakeShared(float animationTime, float targetX = NAN, float targetY = NAN, float targetZ = NAN) {
		return std::make_shared<AstrumMovementAnimator>(animationTime, targetX, targetY, targetZ);
	}
};
#pragma once
#include "AstrumAnimator.hpp"

struct AstrumMovementAnimator :  public AstrumAnimator {
public:
	AstrumMovementAnimator(const AstrumVector3& targetPosition, float animationTime) : next(targetPosition), AstrumAnimator(animationTime) {}

	virtual void Prepare() override {
		previous = owner->GetPosition();
	}
protected:
	virtual void Apply(double percent) override {
		owner->SetPosition(previous + (next - previous) * static_cast<float>(percent));
	}
	
private:
	AstrumVector3 previous{};
	AstrumVector3 next{};

public:
	static std::shared_ptr<AstrumMovementAnimator> MakeShared(const AstrumVector3& targetPosition, float animationTime = 1.f) {
		return std::make_shared<AstrumMovementAnimator>(targetPosition, animationTime);
	}
};
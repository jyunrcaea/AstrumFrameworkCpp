#pragma once
#include "IAstrumAnimator.hpp"

struct AstrumRotationAnimator : public IAstrumAnimator {
public:
	AstrumRotationAnimator(const AstrumVector3& targetRotation, float animationTime) : next(targetRotation), IAstrumAnimator(animationTime) {}

	virtual void Prepare() override {
		previous = owner->GetRotation();
	}
protected:
	virtual void Apply(double percent) override {
		owner->SetRotation(previous + (next - previous) * static_cast<float>(percent));
	}

private:
	AstrumVector3 previous{};
	AstrumVector3 next{};

public:
	static std::shared_ptr<AstrumRotationAnimator> MakeShared(const AstrumVector3& targetRotation, float animationTime) {
		return std::make_shared<AstrumRotationAnimator>(targetRotation, animationTime);
	}
};
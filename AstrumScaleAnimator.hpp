#pragma once
#include "AstrumAnimator.hpp"

struct AstrumScaleAnimator : public AstrumAnimator {
public:
	AstrumScaleAnimator(const AstrumVector3& targetScale, float animationTime) : next(targetScale), AstrumAnimator(animationTime) {}

	virtual void Prepare() override {
		previous = owner->GetScale();
	}
protected:
	virtual void Apply(double percent) override {
		owner->SetScale(previous + (next - previous) * static_cast<float>(percent));
	}

private:
	AstrumVector3 previous{};
	AstrumVector3 next{};

public:
	static std::shared_ptr<AstrumScaleAnimator> MakeShared(const AstrumVector3& targetScale, float animationTime) {
		return std::make_shared<AstrumScaleAnimator>(targetScale, animationTime);
	}
};
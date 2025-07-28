#pragma once
#include "IAstrumAnimator.hpp"

struct AstrumMovementAnimator :  public IAstrumAnimator {
public:
	AstrumMovementAnimator(const AstrumVector3& target, float animationTime) : next(target), IAstrumAnimator(animationTime) { }

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
	static std::shared_ptr<AstrumMovementAnimator> MakeShared(const AstrumVector3& target, float animationTime) {
		return std::make_shared<AstrumMovementAnimator>(target, animationTime);
	}
};
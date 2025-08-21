#pragma once
#include <memory>
#include "AstrumComponent.hpp"
#include "../Animations/IAstrumAnimator.hpp"

class AstrumAnimatorComponent : public AstrumComponent
{
public:
	AstrumAnimatorComponent() { }
	AstrumAnimatorComponent(const std::shared_ptr<IAstrumAnimator>& animator) : animator(animator) { }

	virtual void Prepare() override;
	virtual void Update() override;
	virtual void Release() override;
	// 애니메이션을 재할당 합니다.
	void ResetAnimator(const std::shared_ptr<IAstrumAnimator>& newAnimator);
	//애니메이션을 제거합니다.
	void ClearAnimator();
	std::shared_ptr<IAstrumAnimator> GetAnimator() const;

private:
	std::shared_ptr<IAstrumAnimator> animator = nullptr;

public:
	inline static std::shared_ptr<AstrumAnimatorComponent> MakeShared() {
		return std::make_shared<AstrumAnimatorComponent>();
	}
	inline static std::shared_ptr<AstrumAnimatorComponent> MakeShared(const std::shared_ptr<IAstrumAnimator>& animator) {
		return std::make_shared<AstrumAnimatorComponent>(animator);
	}
};
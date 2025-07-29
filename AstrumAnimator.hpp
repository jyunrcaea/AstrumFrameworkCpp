#pragma once
#include "AstrumChrono.hpp"
#include "IAstrumObject.hpp"
#include "IAstrumAnimator.hpp"

// 미구현 추상 함수: Prepare, Apply
class AstrumAnimator : public IAstrumAnimator {
public:
	AstrumAnimator(float animationTime);
	
	std::function<void()> OnAnimationEnding = nullptr;
	// 애니메이션 함수. (입력값은 0.0 ~ 1.0 사이), AstrumAnimationFunctions 클래스에서 다양한 애니메이션 함수를 제공합니다
	std::function<double(double)> AnimationFunction = [](double x) { return x; };
	
	virtual void Prepare() override = 0;
	virtual void Update() override;
	virtual void Done() override;
	virtual void Stop(bool invokeCallback = false) override;
	virtual void Undo() override;
	virtual void Reset(float startTime = -1) override;

	virtual void SetOwner(IAstrumObject* obj) override;
	virtual void SetStartTime(double time) override;
	virtual void SetAnimationTime(double time) override;

	virtual IAstrumObject* GetOwner() const override;
	virtual double GetStartTime() const override;
	virtual double GetAnimationTime() const override;
	virtual AstrumAnimatingStatusType GetStatus() const override;

protected:
	//변화율을 받아 적용합니다.
	virtual void Apply(double percent) = 0;
	double GetProgress(double current) const;

	double startTime = 0;
	double animationTime = 100;
	IAstrumObject* owner = nullptr;
	AstrumAnimatingStatusType status = AstrumAnimatingStatusType::AstrumAnimatingStatusType_Wait;

private:
	virtual std::function<void()> GetAnimationEndingFunction() override;
	virtual std::function<double(double)> GetAnimationFunction() override;
};
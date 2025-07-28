#pragma once
#include <functional>
#include "AstrumChrono.hpp"
#include "IAstrumObject.hpp"

// 음의 정수는 더이상 갱신되지 않는 상태를 나타냅니다.
enum AstrumAnimatingStatusType {
	// 애니메이션이 중단됨.
	AstrumAnimatingStatusType_Stop = -3,
	// 애니메이션이 취소됨.
	AstrumAnimatingStatusType_Undo = -2,
	// 애니메이션이 완료됨.
	AstrumAnimatingStatusType_End = -1,
	// 애니메이션이 아직 시작되지 않음.
	AstrumAnimatingStatusType_Wait = 0,
	// 애니메이션을 적용하는 중.
	AstrumAnimatingStatusType_Animating = 1,
};

// 미구현 추상 함수: Prepare, Apply
struct IAstrumAnimator {
public:
	IAstrumAnimator(float animationTime) : AnimationTime(animationTime) { StartTime = static_cast<float>(AstrumChrono::GetRunningTime()); }
	// 애니메이션의 시작 시간입니다. AstrumChrono::GetRunningTime()을 기반으로 합니다. (기본값은 생성자가 호출된 시각입니다.)
	float StartTime = 0;
	float AnimationTime = 100;
	std::function<void()> OnAnimationEnding;
	// 진행률을 통해 얼마나 변화할지 계산하는 애니메이션 함수입니다. 기본값은 선형입니다. (0.0 ~ 1.0 사이)
	std::function<double(double)> AnimationFunction = [](double x) { return x; };
	
	// 애니메이터를 준비합니다. IAstrumObject* owner가 할당된 상태여야만 합니다.
	virtual void Prepare() = 0;
	// 애니메이션을 갱신합니다.
	virtual void Update() {
		if (status < 0) return;
		double now = GetProgress(AstrumChrono::GetRunningTime());
		if (now < 0) return;
		if (now >= 1) {
			Done();
			return;
		}

		status = AstrumAnimatingStatusType::AstrumAnimatingStatusType_Animating;
		Apply(AnimationFunction(now));
	}

	// 애니메이션을 즉시 완료합니다.
	virtual void Done() {
		Apply(1.0);
		if (OnAnimationEnding) OnAnimationEnding();
		status = AstrumAnimatingStatusType::AstrumAnimatingStatusType_End;
	}
	// 애니메이션을 마무리 없이 즉시 종료합니다. 
	virtual void Stop(bool invokeCallback = false) { 
		if (invokeCallback && OnAnimationEnding) OnAnimationEnding(); 
		status = AstrumAnimatingStatusType::AstrumAnimatingStatusType_Stop;
	}
	// 애니메이션을 취소합니다. (이전 상태로 돌아갑니다.)
	virtual void Undo() { 
		Apply(0.0);
		status = AstrumAnimatingStatusType::AstrumAnimatingStatusType_Undo;
	}

	void SetOwner(IAstrumObject* obj) { owner = obj; }
	IAstrumObject* GetOwner() const { return owner; }
	AstrumAnimatingStatusType GetStatus() const { return status; }
protected:
	//변화율을 받아 적용합니다.
	virtual void Apply(double percent) = 0;
	double GetProgress(double current) const { return (current - StartTime) / AnimationTime; }

	IAstrumObject* owner = nullptr;
	AstrumAnimatingStatusType status = AstrumAnimatingStatusType::AstrumAnimatingStatusType_Wait;
};
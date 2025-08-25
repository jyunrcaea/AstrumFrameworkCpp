#pragma once
#include <functional>

// 음의 정수는 더이상 갱신되지 않는 종료된 상태를 나타냅니다.
enum AstrumAnimatingStatusType {
	// 애니메이션이 중단됨.
	AstrumAnimatingStatusType_Stop = -3,
	// 애니메이션이 취소됨.
	AstrumAnimatingStatusType_Undo = -2,
	// 애니메이션이 완료됨. 
	AstrumAnimatingStatusType_End = -1,
	// 애니메이션이 아직 시작되지 않음. (또는 시작시간이 되었더라도, 한번이라도 적용된 적이 아직 없음.)
	AstrumAnimatingStatusType_Wait = 0,
	// 애니메이션을 적용하는 중. (또는 종료시간이 되었더라도, 목표 값으로 아직 갱신되지 않음.)
	AstrumAnimatingStatusType_Animating = 1,
};

struct IAstrumAnimator {
	virtual ~IAstrumAnimator() = default;

	// 애니메이터를 준비합니다. IAstrumObject* owner가 할당된 상태여야만 합니다.
	virtual void Prepare() = 0;
	// 애니메이션을 갱신합니다.
	virtual void Update() = 0;
	// 애니메이션을 즉시 완료합니다.
	virtual void Done() = 0;
	// 애니메이션을 마무리 없이 즉시 종료합니다. 
	virtual void Stop(bool invokeCallback = false) = 0;
	// 애니메이션을 취소합니다. (이전 상태로 돌아갑니다.)
	virtual void Undo() = 0;
	// 애니메이션을 초기화합니다. (이미 재생중인 경우 Stop(false)를 호출합니다.)
	// 시작 시간(startTime)이 음수인 경우 현재 시간을 가져옵니다.
	virtual void Reset(float startTime = -1) = 0;

	virtual void SetOwner(IAstrumObject* obj) = 0;
	virtual IAstrumObject* GetOwner() const = 0;
	virtual AstrumAnimatingStatusType GetStatus() const = 0;

	// 애니메이션의 시작 시간입니다. AstrumChrono::GetRunningTime()을 기반으로 합니다. (기본값은 생성자가 호출된 시각입니다.)
	virtual double GetStartTime() const = 0;
	// 애니메이션 유지 시간입니다.
	virtual double GetAnimationTime() const = 0;

	// 애니메이션의 시작 시간을 설정합니다. (이미 재생중인 경우 Stop(false)를 호출합니다.)
	virtual void SetStartTime(double time) = 0;
	virtual void SetAnimationTime(double time) = 0;

	virtual void AddStartTime(double time) { SetStartTime(GetStartTime() + time); }
	virtual void AddAnimationTime(double time) { SetAnimationTime(GetAnimationTime() + time); }

	// 애니메이션이 종료될때 호출될 함수입니다.
	virtual std::function<void()> GetAnimationEndingFunction() = 0;
	// 진행률을 통해 얼마나 변화할지 계산하는 애니메이션 함수입니다. 기본값은 선형입니다.
	virtual std::function<double(double)> GetAnimationFunction() = 0;
};
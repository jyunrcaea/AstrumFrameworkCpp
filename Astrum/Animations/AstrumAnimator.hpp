#pragma once
#include "../Singletons/AstrumChrono.hpp"
#include "../Objects/IAstrumObject.hpp"
#include "IAstrumAnimator.hpp"

/// <summary>
/// 애니메이션을 관리하고 실행하는 추상 클래스입니다.
/// Prepare와 Apply 메서드는 파생 클래스에서 구현해야 합니다.
/// </summary>
class AstrumAnimator : public IAstrumAnimator {
public:
	/// <summary>
	/// 애니메이터를 생성합니다.
	/// </summary>
	/// <param name="animationTime">애니메이션 지속 시간(초)입니다.</param>
	AstrumAnimator(float animationTime);
	
	/// <summary>
	/// 애니메이션이 완료될 때 호출되는 콜백 함수입니다.
	/// </summary>
	std::function<void()> OnAnimationEnding = nullptr;
	/// <summary>
	/// 진행률(0.0~1.0)을 받아 변화율을 계산하는 애니메이션 함수입니다.
	/// AstrumAnimationFunctions 클래스에서 다양한 애니메이션 함수를 제공합니다.
	/// 기본값은 선형 함수입니다.
	/// </summary>
	std::function<double(double)> AnimationFunction = [](double x) { return x; };
	
	/// <summary>
	/// 애니메이터를 준비합니다. 소유 객체가 할당된 상태에서 호출해야 합니다.
	/// 파생 클래스에서 구현해야 합니다.
	/// </summary>
	virtual void Prepare() override = 0;
	/// <summary>
	/// 애니메이션을 갱신합니다. 매 프레임마다 호출되어야 합니다.
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// 애니메이션을 즉시 완료하고 콜백을 호출합니다.
	/// </summary>
	virtual void Done() override;
	/// <summary>
	/// 애니메이션을 즉시 종료합니다. 콜백 호출 여부를 선택할 수 있습니다.
	/// </summary>
	/// <param name="invokeCallback">true이면 완료 콜백을 호출하고, false이면 호출하지 않습니다. 기본값은 false입니다.</param>
	virtual void Stop(bool invokeCallback = false) override;
	/// <summary>
	/// 애니메이션을 취소하고 이전 상태로 복구합니다.
	/// </summary>
	virtual void Undo() override;
	/// <summary>
	/// 애니메이션을 초기화합니다. 이미 재생 중인 경우 Stop(false)를 호출합니다.
	/// </summary>
	/// <param name="startTime">애니메이션 시작 시간입니다. 음수이면 현재 시간을 사용합니다. 기본값은 -1입니다.</param>
	virtual void Reset(float startTime = -1) override;

	/// <summary>
	/// 애니메이션의 소유 객체를 설정합니다.
	/// </summary>
	/// <param name="obj">소유 객체입니다.</param>
	virtual void SetOwner(IAstrumObject* obj) override;
	/// <summary>
	/// 애니메이션의 시작 시간을 설정합니다. 이미 재생 중인 경우 Stop(false)를 호출합니다.
	/// </summary>
	/// <param name="time">설정할 시작 시간입니다.</param>
	virtual void SetStartTime(double time) override;
	/// <summary>
	/// 애니메이션의 지속 시간을 설정합니다.
	/// </summary>
	/// <param name="time">설정할 지속 시간(초)입니다.</param>
	virtual void SetAnimationTime(double time) override;

	/// <summary>
	/// 애니메이션의 소유 객체를 반환합니다.
	/// </summary>
	/// <returns>소유 객체 포인터입니다.</returns>
	virtual IAstrumObject* GetOwner() const override;
	/// <summary>
	/// 애니메이션의 시작 시간을 반환합니다. AstrumChrono::GetRunningTime()을 기반으로 합니다.
	/// </summary>
	/// <returns>시작 시간입니다.</returns>
	virtual double GetStartTime() const override;
	/// <summary>
	/// 애니메이션의 지속 시간을 반환합니다.
	/// </summary>
	/// <returns>지속 시간(초)입니다.</returns>
	virtual double GetAnimationTime() const override;
	/// <summary>
	/// 애니메이션의 현재 상태를 반환합니다.
	/// </summary>
	/// <returns>현재 애니메이션 상태입니다.</returns>
	virtual AstrumAnimatingStatusType GetStatus() const override;

protected:
	/// <summary>
	/// 진행률을 받아 애니메이션을 적용합니다. 파생 클래스에서 구현해야 합니다.
	/// </summary>
	/// <param name="percent">진행률(0.0~1.0)입니다.</param>
	virtual void Apply(double percent) = 0;
	/// <summary>
	/// 현재 시간 기반으로 애니메이션의 진행률을 계산합니다.
	/// </summary>
	/// <param name="current">현재 시간입니다.</param>
	/// <returns>계산된 진행률(0.0~1.0)입니다.</returns>
	double GetProgress(double current) const;

	/// <summary>
	/// 애니메이션의 시작 시간입니다.
	/// </summary>
	double startTime = 0;
	/// <summary>
	/// 애니메이션의 지속 시간(초)입니다.
	/// </summary>
	double animationTime = 100;
	/// <summary>
	/// 애니메이션의 소유 객체입니다.
	/// </summary>
	IAstrumObject* owner = nullptr;
	/// <summary>
	/// 애니메이션의 현재 상태입니다.
	/// </summary>
	AstrumAnimatingStatusType status = AstrumAnimatingStatusType::AstrumAnimatingStatusType_Wait;

private:
	/// <summary>
	/// 애니메이션 완료 콜백 함수를 반환합니다.
	/// </summary>
	/// <returns>애니메이션 완료 시 호출될 함수입니다.</returns>
	virtual std::function<void()> GetAnimationEndingFunction() override;
	/// <summary>
	/// 애니메이션 진행률 계산 함수를 반환합니다.
	/// </summary>
	/// <returns>진행률을 변환하는 애니메이션 함수입니다.</returns>
	virtual std::function<double(double)> GetAnimationFunction() override;
};
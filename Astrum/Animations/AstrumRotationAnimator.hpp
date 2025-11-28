#pragma once
#include "AstrumAnimator.hpp"

/// <summary>
/// 게임 객체의 회전을 시간에 따라 애니메이션하는 구조체입니다.
/// 선형 보간(Lerp)을 사용하여 부드러운 회전 효과를 만듭니다.
/// NaN 값을 사용하여 특정 축(X, Y, Z)만 선택적으로 애니메이션할 수 있습니다.
/// 회전 각도는 도(degree) 단위입니다.
/// </summary>
struct AstrumRotationAnimator : public AstrumAnimator {
public:
	/// <summary>
	/// 목표 회전 벡터로 회전 애니메이터를 생성합니다.
	/// </summary>
	/// <param name="targetRotation">도달할 목표 회전(도)입니다.</param>
	/// <param name="animationTime">애니메이션 지속 시간(초)입니다.</param>
	AstrumRotationAnimator(const AstrumVector3& targetRotation, float animationTime) : next(targetRotation), AstrumAnimator(animationTime) {}
	/// <summary>
	/// 개별 축 회전으로 회전 애니메이터를 생성합니다.
	/// </summary>
	/// <param name="animationTime">애니메이션 지속 시간(초)입니다.</param>
	/// <param name="targetX">목표 X축 회전(도)입니다. NaN이면 X축은 애니메이션하지 않습니다.</param>
	/// <param name="targetY">목표 Y축 회전(도)입니다. NaN이면 Y축은 애니메이션하지 않습니다.</param>
	/// <param name="targetZ">목표 Z축 회전(도)입니다. NaN이면 Z축은 애니메이션하지 않습니다.</param>
	AstrumRotationAnimator(float animationTime, float targetX = NAN, float targetY = NAN, float targetZ = NAN) : next(targetX, targetY, targetZ), AstrumAnimator(animationTime) {}

	/// <summary>
	/// 애니메이션을 준비합니다. 현재 회전을 기록합니다.
	/// </summary>
	virtual void Prepare() override {
		previous = owner->GetRotation();
	}
protected:
	/// <summary>
	/// 진행률에 따라 회전을 보간하여 적용합니다.
	/// </summary>
	/// <param name="percent">애니메이션 진행률입니다. (0.0~1.0)</param>
	virtual void Apply(double percent) override {
		if (false == std::isnan(next.X)) {
			owner->GetRotation().SetX(static_cast<float>(std::lerp(previous.X, next.X, percent)));
		}
		if (false == std::isnan(next.Y)) {
			owner->GetRotation().SetY(static_cast<float>(std::lerp(previous.Y, next.Y, percent)));
		}
		if (false == std::isnan(next.Z)) {
			owner->GetRotation().SetZ(static_cast<float>(std::lerp(previous.Z, next.Z, percent)));
		}
	}

private:
	/// <summary>
	/// 애니메이션 시작 회전(도)입니다.
	/// </summary>
	AstrumVector3 previous{};
	/// <summary>
	/// 애니메이션 목표 회전(도)입니다.
	/// </summary>
	AstrumVector3 next{};

public:
	/// <summary>
	/// 목표 회전으로 회전 애니메이터의 공유 포인터를 생성합니다.
	/// NaN 값을 사용하여 특정 축만 애니메이션할 수 있습니다.
	/// </summary>
	/// <param name="targetRotation">도달할 목표 회전(도)입니다.</param>
	/// <param name="animationTime">애니메이션 지속 시간(초)입니다.</param>
	/// <returns>새로 생성된 AstrumRotationAnimator 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumRotationAnimator> MakeShared(const AstrumVector3& targetRotation, float animationTime) {
		return std::make_shared<AstrumRotationAnimator>(targetRotation, animationTime);
	}
	/// <summary>
	/// 개별 축 회전으로 회전 애니메이터의 공유 포인터를 생성합니다.
	/// NaN 값을 사용하여 특정 축만 애니메이션할 수 있습니다.
	/// </summary>
	/// <param name="animationTime">애니메이션 지속 시간(초)입니다.</param>
	/// <param name="targetX">목표 X축 회전(도)입니다. NaN이면 X축은 애니메이션하지 않습니다.</param>
	/// <param name="targetY">목표 Y축 회전(도)입니다. NaN이면 Y축은 애니메이션하지 않습니다.</param>
	/// <param name="targetZ">목표 Z축 회전(도)입니다. NaN이면 Z축은 애니메이션하지 않습니다.</param>
	/// <returns>새로 생성된 AstrumRotationAnimator 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumRotationAnimator> MakeShared(float animationTime, float targetX = NAN, float targetY = NAN, float targetZ = NAN) {
		return std::make_shared<AstrumRotationAnimator>(animationTime, targetX, targetY, targetZ);
	}
};
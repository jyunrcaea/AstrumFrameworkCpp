#pragma once
#include <cmath>
#include "AstrumAnimator.hpp"

namespace Astrum {
	struct MovementAnimator :  public Animator {
	public:
		MovementAnimator(const Vector3& targetPosition, float animationTime) : next(targetPosition), Animator(animationTime) {}
		MovementAnimator(float animationTime, float targetX = NAN, float targetY = NAN, float targetZ = NAN) : next(targetX, targetY, targetZ), Animator(animationTime) {}

		virtual void Prepare() override {
			previous = owner->GetPosition();
		}
	protected:
		virtual void Apply(double percent) override {
			if (false == std::isnan(next.X)) {
				owner->GetPosition().SetX(static_cast<float>(std::lerp(previous.X, next.X, percent)));
			}
			if (false == std::isnan(next.Y)) {
				owner->GetPosition().SetY(static_cast<float>(std::lerp(previous.Y, next.Y, percent)));
			}
			if (false == std::isnan(next.Z)) {
				owner->GetPosition().SetZ(static_cast<float>(std::lerp(previous.Z, next.Z, percent)));
			}
		}
		
	private:
		Vector3 previous{};
		Vector3 next{};

	public:
		// float 값이 NaN일경우 해당 좌표 축은 업데이트 하지 않습니다.
		static std::shared_ptr<MovementAnimator> MakeShared(const Vector3& targetPosition, float animationTime = 1.f) {
			return std::make_shared<MovementAnimator>(targetPosition, animationTime);
		}
		// float 값이 NaN일경우 해당 좌표 축은 업데이트 하지 않습니다.
		static std::shared_ptr<MovementAnimator> MakeShared(float animationTime, float targetX = NAN, float targetY = NAN, float targetZ = NAN) {
			return std::make_shared<MovementAnimator>(animationTime, targetX, targetY, targetZ);
		}
	};
}
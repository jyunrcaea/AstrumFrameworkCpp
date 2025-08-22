#pragma once
#include "AstrumAnimator.hpp"

namespace Astrum {
	struct RotationAnimator : public Animator {
	public:
		RotationAnimator(const Vector3& targetRotation, float animationTime) : next(targetRotation), Animator(animationTime) {}
		RotationAnimator(float animationTime, float targetX = NAN, float targetY = NAN, float targetZ = NAN) : next(targetX, targetY, targetZ), Animator(animationTime) {}

		virtual void Prepare() override {
			previous = owner->GetRotation();
		}
	protected:
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
		Vector3 previous{};
		Vector3 next{};

	public:
		// float 값이 NaN일경우 해당 좌표 축은 업데이트 하지 않습니다.
		static std::shared_ptr<RotationAnimator> MakeShared(const Vector3& targetRotation, float animationTime) {
			return std::make_shared<RotationAnimator>(targetRotation, animationTime);
		}
		// float 값이 NaN일경우 해당 좌표 축은 업데이트 하지 않습니다.
		static std::shared_ptr<RotationAnimator> MakeShared(float animationTime, float targetX = NAN, float targetY = NAN, float targetZ = NAN) {
			return std::make_shared<RotationAnimator>(animationTime, targetX, targetY, targetZ);
		}
	};
}
#pragma once
#include "AstrumAnimator.hpp"

namespace Astrum {
	struct ScaleAnimator : public Animator {
	public:
		ScaleAnimator(const Vector3& targetScale, float animationTime) : next(targetScale), Animator(animationTime) {}
		ScaleAnimator(float animationTime, float targetX = NAN, float targetY = NAN, float targetZ = NAN) : next(targetX, targetY, targetZ), Animator(animationTime) {}

		virtual void Prepare() override {
			previous = owner->GetScale();
		}
	protected:
		virtual void Apply(double percent) override {
			if (false == std::isnan(next.X)) {
				owner->GetScale().SetX(static_cast<float>(std::lerp(previous.X, next.X, percent)));
			}
			if (false == std::isnan(next.Y)) {
				owner->GetScale().SetY(static_cast<float>(std::lerp(previous.Y, next.Y, percent)));
			}
			if (false == std::isnan(next.Z)) {
				owner->GetScale().SetZ(static_cast<float>(std::lerp(previous.Z, next.Z, percent)));
			}
		}

	private:
		Vector3 previous{};
		Vector3 next{};

	public:
		// float 값이 NaN일경우 해당 좌표 축은 업데이트 하지 않습니다.
		static std::shared_ptr<ScaleAnimator> MakeShared(const Vector3& targetScale, float animationTime) {
			return std::make_shared<ScaleAnimator>(targetScale, animationTime);
		}
		// float 값이 NaN일경우 해당 좌표 축은 업데이트 하지 않습니다.
		static std::shared_ptr<ScaleAnimator> MakeShared(float animationTime, float targetX = NAN, float targetY = NAN, float targetZ = NAN) {
			return std::make_shared<ScaleAnimator>(animationTime, targetX, targetY, targetZ);
		}
	};
}
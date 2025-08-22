#pragma once
#include <memory>
#include "AstrumComponent.hpp"
#include "../Animations/IAstrumAnimator.hpp"

namespace Astrum {
	class AnimatorComponent : public Component
	{
	public:
		AnimatorComponent() { }
		AnimatorComponent(const std::shared_ptr<IAnimator>& animator) : animator(animator) { }

		virtual void Prepare() override;
		virtual void Update() override;
		virtual void Release() override;
		// 애니메이션을 재할당 합니다.
		void ResetAnimator(const std::shared_ptr<IAnimator>& newAnimator);
		//애니메이션을 제거합니다.
		void ClearAnimator();
		std::shared_ptr<IAnimator> GetAnimator() const;

	private:
		std::shared_ptr<IAnimator> animator = nullptr;

	public:
		inline static std::shared_ptr<AnimatorComponent> MakeShared() {
			return std::make_shared<AnimatorComponent>();
		}
		inline static std::shared_ptr<AnimatorComponent> MakeShared(const std::shared_ptr<IAnimator>& animator) {
			return std::make_shared<AnimatorComponent>(animator);
		}
	};
}
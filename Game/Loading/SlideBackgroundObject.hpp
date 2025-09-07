#pragma once
#include "../../Astrum/Objects/AstrumGroupObject.hpp"
#include "../../Astrum/Objects/AstrumMaterialObject.hpp"
#include "../../Astrum/Components/AstrumAnimatorComponent.hpp"
#include "../../Astrum/Singletons/AstrumTextureCache.hpp"
#include "../../Astrum/Animations/AstrumMovementAnimator.hpp"
#include "../../Astrum/Animations/AstrumAnimationFunctions.hpp"
#include "../../Astrum/Singletons/AstrumWindow.hpp"

namespace Loading {
	constexpr float SlideBackgroundObjectAnimationTime = 0.5f;

	class SlideBackgroundObject : public AstrumGroupObject
	{
	public:
		SlideBackgroundObject() {
			//const float windowWidth = static_cast<float>(AstrumWindow::GetWidth());
			const float windowHeight = static_cast<float>(AstrumWindow::GetHeight());

			AddObject(leftObject = AstrumMaterialObject::MakeShared(
				AstrumTextureCache::Load("loading_left.png")
			));
			leftObject->AddComponent(leftMovementComponent = AstrumAnimatorComponent::MakeShared());
			centerToLeft->AnimationFunction = AstrumAnimationFunctions::EaseOutSine;
			leftToCenter->AnimationFunction = AstrumAnimationFunctions::EaseOutSine;
			leftObject->SetPositionZ(1);
			
			float leftScale = windowHeight / leftObject->GetTexture()->GetHeight();
			leftObject->SetScale({ leftScale, leftScale, 1.f });

			AddObject(rightObject = AstrumMaterialObject::MakeShared(
				AstrumTextureCache::Load("loading_right.png")
			));
			rightObject->AddComponent(rightMovementComponent = AstrumAnimatorComponent::MakeShared());
			centerToRight->AnimationFunction = AstrumAnimationFunctions::EaseOutSine;
			rightToCenter->AnimationFunction = AstrumAnimationFunctions::EaseOutSine;
			rightObject->SetPositionZ(2);

			float rightScale = windowHeight / rightObject->GetTexture()->GetHeight();
			rightObject->SetScale({ rightScale, rightScale, 1.f });
		}

		void ToClose() {
			leftMovementComponent->ResetAnimator(leftToCenter);
			rightMovementComponent->ResetAnimator(rightToCenter);

			leftToCenter->Reset();
			rightToCenter->Reset();
		}
		void SetCloseFunction(const std::function<void()>& action) {
			leftToCenter->OnAnimationEnding = action;
		}

		void ToOpen() {
			leftMovementComponent->ResetAnimator(centerToLeft);
			rightMovementComponent->ResetAnimator(centerToRight);

			centerToLeft->Reset();
			centerToRight->Reset();
		}
		void SetOpenFunction(const std::function<void()>& action) {
			centerToLeft->OnAnimationEnding = action;
		}
		
	private:
		std::shared_ptr<AstrumMaterialObject> leftObject = nullptr;
		std::shared_ptr<AstrumMaterialObject> rightObject = nullptr;

		std::shared_ptr<AstrumAnimatorComponent> leftMovementComponent = nullptr;
		std::shared_ptr<AstrumAnimatorComponent> rightMovementComponent = nullptr;

		std::shared_ptr<AstrumMovementAnimator> leftToCenter = AstrumMovementAnimator::MakeShared(SlideBackgroundObjectAnimationTime, 0, NAN, NAN);
		std::shared_ptr<AstrumMovementAnimator> rightToCenter = AstrumMovementAnimator::MakeShared(SlideBackgroundObjectAnimationTime, 0, NAN, NAN);
		std::shared_ptr<AstrumMovementAnimator> centerToLeft = AstrumMovementAnimator::MakeShared(SlideBackgroundObjectAnimationTime, static_cast<float>(-AstrumWindow::GetWidth()), NAN, NAN);
		std::shared_ptr<AstrumMovementAnimator> centerToRight = AstrumMovementAnimator::MakeShared(SlideBackgroundObjectAnimationTime, static_cast<float>(AstrumWindow::GetWidth()), NAN, NAN);

	};
}
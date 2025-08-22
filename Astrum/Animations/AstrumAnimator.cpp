#include "AstrumAnimator.hpp"

namespace Astrum {
	double Animator::GetStartTime() const { return startTime; }
	double Animator::GetAnimationTime() const { return animationTime; }

	Animator::Animator(float animationTime)
		: animationTime(animationTime)
	{
		startTime = static_cast<float>(Chrono::GetRunningTime());
	}

	void Animator::Update() {
		if (status < 0) return;
		double now = GetProgress(Chrono::GetRunningTime());
		if (now < 0) return;
		if (now >= 1) {
			Done();
			return;
		}

		status = AnimatingStatusType::AnimatingStatusType_Animating;
		Apply(AnimationFunction(now));
	}
	void Animator::Done() {
		Apply(1.0);
		if (OnAnimationEnding) OnAnimationEnding();
		status = AnimatingStatusType::AnimatingStatusType_End;
	}
	void Animator::Stop(bool invokeCallback) {
		if (invokeCallback && OnAnimationEnding) OnAnimationEnding();
		status = AnimatingStatusType::AnimatingStatusType_Stop;
	}
	void Animator::Undo() {
		Apply(0.0);
		status = AnimatingStatusType::AnimatingStatusType_Undo;
	}
	void Animator::Reset(float newStartTime) {
		if (status > 0) Stop(false);
		this->startTime = (newStartTime < 0 ? static_cast<float>(Chrono::GetRunningTime()) : newStartTime);
		status = AnimatingStatusType::AnimatingStatusType_Wait;
	}

	void Animator::SetOwner(IObject* obj) { owner = obj; }
	void Animator::SetStartTime(double time) {
		startTime = time;
		if (status > 0) Stop(false);
		status = AnimatingStatusType::AnimatingStatusType_Wait;
	}
	void Animator::SetAnimationTime(double time) { animationTime = time; }
	IObject* Animator::GetOwner() const { return owner; }
	AnimatingStatusType Animator::GetStatus() const { return status; }

	double Animator::GetProgress(double current) const {
		// animationTime이 0일 경우 음 또는 양의 무한이 나오므로 clamp.
		return std::clamp((current - startTime) / animationTime, -1.0, 2.0);
	}

	std::function<void()> Animator::GetAnimationEndingFunction() { return OnAnimationEnding; }
	std::function<double(double)> Animator::GetAnimationFunction() { return AnimationFunction; }
}
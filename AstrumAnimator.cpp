#include "AstrumAnimator.hpp"

double AstrumAnimator::GetStartTime() const { return startTime; }
double AstrumAnimator::GetAnimationTime() const { return animationTime; }

AstrumAnimator::AstrumAnimator(float animationTime)
	: animationTime(animationTime)
{
	startTime = static_cast<float>(AstrumChrono::GetRunningTime());
}

void AstrumAnimator::Update() {
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
void AstrumAnimator::Done() {
	Apply(1.0);
	if (OnAnimationEnding) OnAnimationEnding();
	status = AstrumAnimatingStatusType::AstrumAnimatingStatusType_End;
}
void AstrumAnimator::Stop(bool invokeCallback) {
	if (invokeCallback && OnAnimationEnding) OnAnimationEnding();
	status = AstrumAnimatingStatusType::AstrumAnimatingStatusType_Stop;
}
void AstrumAnimator::Undo() {
	Apply(0.0);
	status = AstrumAnimatingStatusType::AstrumAnimatingStatusType_Undo;
}
void AstrumAnimator::Reset(float startTime) {
	if (status > 0) Stop(false);
	this->startTime = (startTime < 0 ? static_cast<float>(AstrumChrono::GetRunningTime()) : startTime);
	status = AstrumAnimatingStatusType::AstrumAnimatingStatusType_Wait;
}

void AstrumAnimator::SetOwner(IAstrumObject* obj) { owner = obj; }
void AstrumAnimator::SetStartTime(double time) {
	startTime = time;
	if (status > 0) Stop(false);
	status = AstrumAnimatingStatusType::AstrumAnimatingStatusType_Wait;
}
void AstrumAnimator::SetAnimationTime(double time) { animationTime = time; }
IAstrumObject* AstrumAnimator::GetOwner() const { return owner; }
AstrumAnimatingStatusType AstrumAnimator::GetStatus() const { return status; }

double AstrumAnimator::GetProgress(double current) const { return (current - startTime) / animationTime; }

std::function<void()> AstrumAnimator::GetAnimationEndingFunction() { return OnAnimationEnding; }
std::function<double(double)> AstrumAnimator::GetAnimationFunction() { return AnimationFunction; }
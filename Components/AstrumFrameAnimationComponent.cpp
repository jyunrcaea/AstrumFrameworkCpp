#include "AstrumFrameAnimationComponent.hpp"
#include "../Singletons/AstrumChrono.hpp"

void AstrumFrameAnimationComponent::Update()
{
	if (nullptr == materialOwner) return;
	if (frames.empty()) return;
	const int n = static_cast<int>(frames.size());

	sumTime = static_cast<float>(sumTime + AstrumChrono::GetDeltaTime() * PlaybackSpeed);
	if (sumTime < TimePerFrame) return;

	int nextFrame = FrameIndex;
	while (sumTime >= TimePerFrame) {
		sumTime -= TimePerFrame;
		nextFrame++;
		if (Loop) nextFrame %= n;
		else nextFrame = min(n, nextFrame);
	}
	FrameIndex = static_cast<unsigned short>(nextFrame);

	if (FrameIndex < n) {
		materialOwner->SetMaterial(frames[Reverse ? static_cast<size_t>(n - FrameIndex - 1) : FrameIndex]);
		if (OnFrameChanged) OnFrameChanged(FrameIndex);
	}
	else materialOwner->SetMaterial(frames[Reverse ? 0 : static_cast<size_t>(n - 1)]);
}

void AstrumFrameAnimationComponent::SetOwner(IAstrumObject* owner) {
	if (nullptr == owner) {
		materialOwner = nullptr;
	}
	else if (nullptr == (materialOwner = dynamic_cast<IAstrumMaterialObject*>(owner))) {
		throw AstrumException("AstrumFrameAnimationComponent is required IAstrumMaterialObject.");
	}

	AstrumComponent::SetOwner(owner);
}

std::vector<std::shared_ptr<AstrumMaterial>>& AstrumFrameAnimationComponent::GetFrames() { return frames; }
IAstrumMaterialObject* AstrumFrameAnimationComponent::GetMaterialObjectOwner() const { return materialOwner; }
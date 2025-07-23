#include "AstrumFrameAnimationComponent.h"
#include "IAstrumFrameAnimationComponent.h"

void AstrumFrameAnimationComponent::Update()
{
	if (materialOwner == nullptr) return;
	if (frames.empty()) return;
	const int n = static_cast<int>(frames.size());

	sumTime = static_cast<float>(sumTime + AstrumChrono::Instance().GetDeltaTime() * PlaybackSpeed);
	while (sumTime >= TimePerFrame) {
		sumTime -= TimePerFrame;
		FrameIndex = (FrameIndex + 1) % n;
	}

	materialOwner->SetMaterial(frames[FrameIndex]);
}

void AstrumFrameAnimationComponent::SetOwner(IAstrumObject* owner) {
	if (owner == nullptr) {
		materialOwner = nullptr;
	}
	else if (nullptr == (materialOwner = dynamic_cast<IAstrumMaterialObject*>(owner))) {
		throw AstrumException("AstrumFrameAnimationComponent is required IAstrumMaterialObject.");
	}

	AstrumComponent::SetOwner(owner);
}

std::vector<shared_ptr<AstrumMaterial>>& AstrumFrameAnimationComponent::GetFrames() { return frames; }
IAstrumMaterialObject* AstrumFrameAnimationComponent::GetMaterialObjectOwner() const { return materialOwner; }
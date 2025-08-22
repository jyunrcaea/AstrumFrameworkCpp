#include "AstrumFrameAnimationComponent.hpp"
#include "../Singletons/AstrumChrono.hpp"

namespace Astrum {
	void FrameAnimationComponent::Update()
	{
		if (nullptr == materialOwner) return;
		if (frames.empty()) return;
		const int n = static_cast<int>(frames.size());

		sumTime = static_cast<float>(sumTime + Chrono::GetDeltaTime() * PlaybackSpeed);
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

	void FrameAnimationComponent::SetOwner(IObject* newOwner) {
		if (nullptr == newOwner) {
			materialOwner = nullptr;
		}
		else if (nullptr == (materialOwner = dynamic_cast<IMaterialObject*>(newOwner))) {
			throw Exception("FrameAnimationComponent is required IMaterialObject.");
		}

		Component::SetOwner(newOwner);
	}

	std::vector<std::shared_ptr<Material>>& FrameAnimationComponent::GetFrames() { return frames; }
	IMaterialObject* FrameAnimationComponent::GetMaterialObjectOwner() const { return materialOwner; }
}
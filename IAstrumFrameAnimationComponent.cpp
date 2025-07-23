#include "IAstrumFrameAnimationComponent.h"

void IAstrumFrameAnimationComponent::SetFrame(int index, const std::shared_ptr<AstrumMaterial>& material)
{
	GetFrames()[index] = material;
}

void IAstrumFrameAnimationComponent::AddFrame(const std::shared_ptr<AstrumMaterial>& material)
{
	GetFrames().push_back(material);
}

size_t IAstrumFrameAnimationComponent::GetFrameCount()
{
	return GetFrames().size();
}
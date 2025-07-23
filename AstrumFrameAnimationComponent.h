#pragma once
#include "AstrumComponent.h"
#include "IAstrumMaterialObject.h"
#include "IAstrumFrameAnimationComponent.h"

class AstrumFrameAnimationComponent : public AstrumComponent, public IAstrumFrameAnimationComponent
{
public:
	virtual void Update() override;

	virtual void SetOwner(IAstrumObject* owner) override;

	unsigned int FrameIndex = 0;
	float TimePerFrame = 1.f;
	float PlaybackSpeed = 1.f;

	std::vector<shared_ptr<AstrumMaterial>>& GetFrames();
	IAstrumMaterialObject* GetMaterialObjectOwner() const;
private:
	std::vector<shared_ptr<AstrumMaterial>> frames;
	IAstrumMaterialObject* materialOwner;
	float sumTime = 0;

	bool loop = false;
};
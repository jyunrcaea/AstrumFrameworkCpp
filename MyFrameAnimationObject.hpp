#pragma once
#include "AstrumMaterialObject.hpp"
#include "AstrumFrameAnimationComponent.h"

class MyFrameAnimationObject : public AstrumMaterialObject {
public:
	MyFrameAnimationObject() {
		AddComponent(frameAnimator = make_shared<AstrumFrameAnimationComponent>());

		frameAnimator->AddFrame(make_shared<AstrumMaterial>(L"./Resource/dotnet.png"));
		frameAnimator->AddFrame(make_shared<AstrumMaterial>(L"./Resource/dotnetbot.png"));
	}

private:
	shared_ptr<AstrumFrameAnimationComponent> frameAnimator;
};

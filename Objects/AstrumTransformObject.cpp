#include "AstrumTransformObject.hpp"

AstrumTransformObject::AstrumTransformObject()
	: Position(0,0,0, std::bind(CallbackObservedPosition, this)),
	Rotation(0,0,0, std::bind(CallbackObservedRotation, this)),
	Scale(1,1,1, std::bind(CallbackObservedScale, this))
{

}

AstrumObservedVector3& AstrumTransformObject::GetPosition() { return Position; }
AstrumObservedVector3& AstrumTransformObject::GetRotation() { return Rotation; }
AstrumObservedVector3& AstrumTransformObject::GetScale() { return Scale; }

const AstrumVector3& AstrumTransformObject::GetAbsolutePosition() {
	if (absoluteTransformLazy & AstrumLazyPropTransformType_Position) {
		UpdateAbsolutePosition();
		absoluteTransformLazy = static_cast<AstrumLazyPropTransformType>(absoluteTransformLazy - AstrumLazyPropTransformType_Position);
	}
	return absolutePosition;
}
const AstrumVector3& AstrumTransformObject::GetAbsoluteRotation() {
	if (absoluteTransformLazy & AstrumLazyPropTransformType_Rotation) {
		UpdateAbsoluteRotation();
		absoluteTransformLazy = static_cast<AstrumLazyPropTransformType>(absoluteTransformLazy - AstrumLazyPropTransformType_Rotation);
	}
	return absoluteRotation;
}
const AstrumVector3& AstrumTransformObject::GetAbsoluteScale() {
	if (absoluteTransformLazy & AstrumLazyPropTransformType_Scale) {
		UpdateAbsoluteScale();
		absoluteTransformLazy = static_cast<AstrumLazyPropTransformType>(absoluteTransformLazy - AstrumLazyPropTransformType_Scale);
	}
	return absoluteScale;
}

void AstrumTransformObject::CallbackObservedPosition() {
	absoluteTransformLazy = static_cast<AstrumLazyPropTransformType>(absoluteTransformLazy | AstrumLazyPropTransformType_Position);
}
void AstrumTransformObject::CallbackObservedRotation() {
	absoluteTransformLazy = static_cast<AstrumLazyPropTransformType>(absoluteTransformLazy | AstrumLazyPropTransformType_Rotation);
}
void AstrumTransformObject::CallbackObservedScale() {
	absoluteTransformLazy = static_cast<AstrumLazyPropTransformType>(absoluteTransformLazy | AstrumLazyPropTransformType_Scale);
}

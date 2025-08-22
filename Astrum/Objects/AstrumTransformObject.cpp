#include "AstrumTransformObject.hpp"

namespace Astrum
{
	TransformObject::TransformObject()
		: Position(0, 0, 0, std::bind(&TransformObject::CallbackObservedPosition, this)),
		Rotation(0, 0, 0, std::bind(&TransformObject::CallbackObservedRotation, this)),
		Scale(1, 1, 1, std::bind(&TransformObject::CallbackObservedScale, this))
	{

	}

	ObservedVector3& TransformObject::GetPosition() { return Position; }
	ObservedVector3& TransformObject::GetRotation() { return Rotation; }
	ObservedVector3& TransformObject::GetScale() { return Scale; }

	const Vector3& TransformObject::GetAbsolutePosition() {
		if (absoluteTransformLazy & LazyPropTransformType_Position) {
			UpdateAbsolutePosition();
			absoluteTransformLazy -= LazyPropTransformType_Position;
		}
		return absolutePosition;
	}
	const Vector3& TransformObject::GetAbsoluteRotation() {
		if (absoluteTransformLazy & LazyPropTransformType_Rotation) {
			UpdateAbsoluteRotation();
			absoluteTransformLazy -= LazyPropTransformType_Rotation;
		}
		return absoluteRotation;
	}
	const Vector3& TransformObject::GetAbsoluteScale() {
		if (absoluteTransformLazy & LazyPropTransformType_Scale) {
			UpdateAbsoluteScale();
			absoluteTransformLazy -= LazyPropTransformType_Scale;
		}
		return absoluteScale;
	}

	void TransformObject::CallbackObservedPosition() {
		absoluteTransformLazy += LazyPropTransformType_Position;
	}
	void TransformObject::CallbackObservedRotation() {
		absoluteTransformLazy += LazyPropTransformType_Rotation;
	}
	void TransformObject::CallbackObservedScale() {
		absoluteTransformLazy += LazyPropTransformType_Scale;
	}
}

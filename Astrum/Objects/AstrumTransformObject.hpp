#pragma once
#include "IAstrumObject.hpp"
#include "IAstrumGroupObject.hpp"
#include "../Vectors/AstrumVector3.hpp"
#include "../Vectors/AstrumObservedVector3.hpp"
#include "../Units/AstrumQuaternion.hpp"
#include "../Collections/AstrumComponentList.hpp"

namespace Astrum
{
	enum LazyPropTransformType : char
	{
		LazyPropTransformType_None = 0,
		LazyPropTransformType_Position = 1,
		LazyPropTransformType_Rotation = 2,
		LazyPropTransformType_Scale = 4
	};

	class TransformObject : public IObject
	{
	public:
		TransformObject();
		virtual ~TransformObject() = default;

		ObservedVector3& GetPosition() override;
		ObservedVector3& GetRotation() override;
		ObservedVector3& GetScale() override;

		virtual const Vector3& GetAbsolutePosition() override;
		virtual const Vector3& GetAbsoluteRotation() override;
		virtual const Vector3& GetAbsoluteScale() override;
	protected:
		// 객체의 좌표입니다. (전체를 재할당 할경우 Absolute 값이 갱신되지 않습니다. Reset() 맴버 함수를 사용해보세요.)
		ObservedVector3 Position;
		// 객체의 회전값입니다. 육십분법을 사용합니다. (전체를 재할당 할경우 Absolute 값이 갱신되지 않습니다. Reset() 맴버 함수를 사용해보세요.)
		ObservedVector3 Rotation;
		// 객체의 크기값입니다. (전체를 재할당 할경우 Absolute 값이 갱신되지 않습니다. Reset() 맴버 함수를 사용해보세요.)
		ObservedVector3 Scale;

	private:
		Vector3 absolutePosition;
		Vector3 absoluteRotation;
		Vector3 absoluteScale;
		// to do : make lazy prop for absolute transform.
		LazyPropTransformType absoluteTransformLazy = LazyPropTransformType::LazyPropTransformType_None;

		bool Visible = true;
		bool isPrepared = false;

		void CallbackObservedPosition();
		void CallbackObservedRotation();
		void CallbackObservedScale();
	};

	inline LazyPropTransformType operator|(LazyPropTransformType left, LazyPropTransformType right) {
		return static_cast<LazyPropTransformType>(static_cast<char>(left) | static_cast<char>(right));
	}
	inline LazyPropTransformType& operator+=(LazyPropTransformType& left, LazyPropTransformType right) {
		return left = static_cast<LazyPropTransformType>(static_cast<char>(left) | static_cast<char>(right));
	}
	inline LazyPropTransformType& operator-=(LazyPropTransformType& left, LazyPropTransformType right) {
		return left = static_cast<LazyPropTransformType>(static_cast<char>(left) & ~static_cast<char>(right));
	}
}
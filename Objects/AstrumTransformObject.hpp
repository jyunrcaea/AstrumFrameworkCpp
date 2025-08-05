#pragma once
#include "IAstrumObject.hpp"
#include "IAstrumGroupObject.hpp"
#include "../Vectors/AstrumVector3.hpp"
#include "../Vectors/AstrumObservedVector3.hpp"
#include "../Units/AstrumQuaternion.hpp"
#include "../Collections/AstrumComponentList.hpp"

enum AstrumLazyPropTransformType : short
{
    AstrumLazyPropTransformType_None = 0,
    AstrumLazyPropTransformType_Position = 1,
    AstrumLazyPropTransformType_Rotation = 2,
    AstrumLazyPropTransformType_Scale = 4
};

class AstrumTransformObject : public IAstrumObject
{
public:
    AstrumTransformObject();
    virtual ~AstrumTransformObject() = default;

    AstrumObservedVector3& GetPosition() override;
    AstrumObservedVector3& GetRotation() override;
    AstrumObservedVector3& GetScale() override;

    virtual const AstrumVector3& GetAbsolutePosition() override;
    virtual const AstrumVector3& GetAbsoluteRotation() override;
    virtual const AstrumVector3& GetAbsoluteScale() override;
protected:
    // 객체의 좌표입니다. (전체를 재할당 할경우 Absolute 값이 갱신되지 않습니다. Reset() 맴버 함수를 사용해보세요.)
    AstrumObservedVector3 Position;
    // 객체의 회전값입니다. 육십분법을 사용합니다. (전체를 재할당 할경우 Absolute 값이 갱신되지 않습니다. Reset() 맴버 함수를 사용해보세요.)
    AstrumObservedVector3 Rotation;
    // 객체의 크기값입니다. (전체를 재할당 할경우 Absolute 값이 갱신되지 않습니다. Reset() 맴버 함수를 사용해보세요.)
    AstrumObservedVector3 Scale;

private:
    AstrumVector3 absolutePosition;
    AstrumVector3 absoluteRotation;
    AstrumVector3 absoluteScale;
    // to do : make lazy prop for absolute transform.
    AstrumLazyPropTransformType absoluteTransformLazy = AstrumLazyPropTransformType::AstrumLazyPropTransformType_None;

    void CallbackObservedPosition();
    void CallbackObservedRotation();
    void CallbackObservedScale();
};


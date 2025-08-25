#pragma once
#include "IAstrumObject.hpp"
#include "IAstrumGroupObject.hpp"
#include "../Vectors/AstrumVector3.hpp"
#include "../Vectors/AstrumObservedVector3.hpp"
#include "../Units/AstrumQuaternion.hpp"
#include "../Collections/AstrumComponentList.hpp"


//게임 객체의 기본 단위.
class AstrumObject : public virtual IAstrumObject
{
public:
    // AstrumObject를 생성합니다. Position 및 Rotation은 기본값 (0,0,0)이며, Scale은 기본값으로 (1,1,1)이 할당되어 있습니다.
    AstrumObject();
    virtual ~AstrumObject() = default;

    // 절대 위치, 회전, 크기를 업데이트하고, 컴포넌트를 준비합니다.
    virtual void Prepare() override;
    // 컴포넌트들을 업데이트 합니다.
    virtual void Update() override;
    // 컴포넌트들을 해제합니다.
    virtual void Release() override;
    virtual void Draw() override;

    AstrumObservedVector3& GetPosition() override;
    AstrumObservedVector3& GetRotation() override;
    AstrumObservedVector3& GetScale() override;

    virtual const AstrumVector3& GetAbsolutePosition() override;
    virtual const AstrumVector3& GetAbsoluteRotation() override;
    virtual const AstrumVector3& GetAbsoluteScale() override;

    IAstrumGroupObject* GetParent() const override;
    virtual bool SetParent(IAstrumGroupObject* const p) override;
    virtual bool ClearParent(IAstrumGroupObject* const p) override;

    virtual IAstrumComponentList& GetComponents() override;
protected:
    // 객체의 좌표입니다. (전체를 재할당 할경우 Absolute 값이 갱신되지 않습니다. Reset() 맴버 함수를 사용해보세요.)
    AstrumObservedVector3 Position;
    // 객체의 회전값입니다. 육십분법을 사용합니다. (전체를 재할당 할경우 Absolute 값이 갱신되지 않습니다. Reset() 맴버 함수를 사용해보세요.)
    AstrumObservedVector3 Rotation;
    // 객체의 크기값입니다. (전체를 재할당 할경우 Absolute 값이 갱신되지 않습니다. Reset() 맴버 함수를 사용해보세요.)
    AstrumObservedVector3 Scale;

    virtual void UpdateAbsolutePosition() override;
    virtual void UpdateAbsoluteRotation() override;
    virtual void UpdateAbsoluteScale() override;

    AstrumComponentList Components;

    void SetAbsolutePosition(const AstrumVector3& vec);
    void SetAbsoluteRotation(const AstrumVector3& vec);
    void SetAbsoluteScale(const AstrumVector3& vec);

public:
    virtual void SetVisible(bool enable) override;

	virtual bool IsVisible() const override;
    virtual bool IsPrepared() const override;

private:
    bool visible = true;
    bool isPrepared = false;

private:
    AstrumVector3 absolutePosition;
    AstrumVector3 absoluteRotation;
    AstrumVector3 absoluteScale;

    IAstrumGroupObject* parent = nullptr; // Parent reference me by shared_ptr, and parent did allocate it. so do not need shared_ptr.
};
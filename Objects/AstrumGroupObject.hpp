#pragma once
#include "AstrumObject.hpp"
#include "../Collections/AstrumObjectList.hpp"
#include "IAstrumGroupObject.hpp"
#include <memory>

class AstrumGroupObject : public virtual AstrumObject, public virtual IAstrumGroupObject {
public:
    virtual bool ClearParent(IAstrumGroupObject* const p) override { return AstrumObject::ClearParent(p); }
    virtual const AstrumVector3& GetAbsolutePosition() const override { return AstrumObject::GetAbsolutePosition(); }
    virtual const AstrumVector3& GetAbsoluteRotation() const override { return AstrumObject::GetAbsoluteRotation(); }
    virtual const AstrumVector3& GetAbsoluteScale() const override { return AstrumObject::GetAbsoluteScale(); }
    virtual IAstrumComponentList& GetComponents() override { return AstrumObject::GetComponents(); }
    virtual IAstrumGroupObject* GetParent() const override { return AstrumObject::GetParent(); }
    virtual AstrumObservedVector3& GetPosition() override { return AstrumObject::GetPosition(); }
    virtual AstrumObservedVector3& GetRotation() override { return AstrumObject::GetRotation(); }
    virtual AstrumObservedVector3& GetScale() override { return AstrumObject::GetScale(); }
    virtual bool IsPrepared() const override { return AstrumObject::IsPrepared(); }
    virtual bool SetParent(IAstrumGroupObject* const p) override { return AstrumObject::SetParent(p); }

public:
    AstrumGroupObject();

    virtual void Prepare() override;
    virtual void Update() override;
    virtual void Release() override;
    virtual void Draw() override;

    virtual IAstrumObjectList& GetObjectList() override;

    virtual void UpdateAbsolutePosition() override;
    virtual void UpdateAbsoluteRotation() override;
    virtual void UpdateAbsoluteScale() override;

private:
    AstrumObjectList objects;
};
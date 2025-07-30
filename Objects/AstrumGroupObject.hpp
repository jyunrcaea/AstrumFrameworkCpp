#pragma once
#include "AstrumObject.hpp"
#include "../Collections/AstrumObjectList.hpp"
#include "IAstrumGroupObject.hpp"
#include <memory>


//여기서 말하는 부모는, 이 객체인데요
class AstrumGroupObject : public AstrumObject, public IAstrumGroupObject {
public:
    AstrumGroupObject();

    void Prepare() override;
    void Update() override;
    void Release() override;
    void Draw() override;

    virtual AstrumObjectList& GetObjectList() override;

    virtual void UpdateAbsolutePosition() override;
    virtual void UpdateAbsoluteRotation() override;
    virtual void UpdateAbsoluteScale() override;

private:
    AstrumObjectList objects;
};
#pragma once
#include <iostream>
#include "AstrumCircleObject.hpp"
#include "AstrumVector3.hpp"
#include "AstrumColor.hpp"

namespace {
    void Logging(const string& name, const AstrumObject* const obj) {
        std::cout << format("{}() : pos {} {} {} scale {} {} {}", name, obj->GetAbsolutePosition().X, obj->GetAbsolutePosition().Y, obj->GetAbsolutePosition().Z, obj->GetAbsoluteScale().X, obj->GetAbsoluteScale().Y, obj->GetAbsoluteScale().Z) << std::endl;
    }
}

class MyCircle : public AstrumCircleObject {
public:
    MyCircle() : AstrumCircleObject(
        AstrumVertexColor(AstrumVector3{ 0.0f, 0.0f }, AstrumColor::LightPeriwinkle), 0.5f, GetCircleSideColor()) {
        position.SetX(-2.0f);
        position.SetZ(2.0f);
    }

    virtual void Prepare() override {
        AstrumObject::Prepare();
        Logging(__FUNCTION__, this);
    }
    virtual void Update() override {
        rotation.AddZ(static_cast<float>(AstrumChrono::Instance().GetDeltaTime() * 1557));
        AstrumObject::Update();
    }

    virtual void Release() override {
        AstrumObject::Release();
        Logging(__FUNCTION__, this);
    }

private:
    vector<AstrumColor> GetCircleSideColor() const {
        vector<AstrumColor> colors;
        colors.reserve(4);
        colors.push_back(AstrumColor::Pink);
        colors.push_back(AstrumColor::Periwinkle);
        colors.push_back(AstrumColor::Lilac);
        colors.push_back(AstrumColor::LightBlue);
        return colors;
    }
};
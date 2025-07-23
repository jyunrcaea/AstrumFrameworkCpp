#pragma once
#include <iostream>
#include "AstrumTriangleObject.hpp"
#include "AstrumVector3.hpp"
#include "AstrumColor.hpp"

namespace {
    void Logging(const string& name, const AstrumObject* const obj) {
        std::cout << format("{}() : pos {} {} {} scale {} {} {}", name, obj->GetAbsolutePosition().X, obj->GetAbsolutePosition().Y, obj->GetAbsolutePosition().Z, obj->GetAbsoluteScale().X, obj->GetAbsoluteScale().Y, obj->GetAbsoluteScale().Z) << std::endl;
    }
}

class MyTriangle : public AstrumTriangleObject {
public:
    MyTriangle() : AstrumTriangleObject(
        AstrumVertexColor(AstrumVector3{ -0.5f, 0.5f }, AstrumColor::LightBlue),
        AstrumVertexColor(AstrumVector3{ 0.5f, 0.5f }, AstrumColor::Periwinkle),
        AstrumVertexColor(AstrumVector3{ 0.0f, -0.5f }, AstrumColor::Lilac)
    ) {
        position.SetX(0.0f);
        position.SetZ(2.0f);
    }

    virtual void Prepare() override {
        AstrumObject::Prepare();
        Logging(__FUNCTION__, this);
    }
    virtual void Update() override {
        rotation.AddZ(static_cast<float>(AstrumChrono::Instance().GetDeltaTime() * 614));
        AstrumObject::Update();
    }

    virtual void Release() override {
        AstrumObject::Release();
        Logging(__FUNCTION__, this);
    }
};
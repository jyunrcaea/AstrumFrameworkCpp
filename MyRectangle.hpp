#pragma once
#include "AstrumRectangleObject.hpp"
#include "AstrumColor.hpp"

class MyRectangle : public AstrumRectangleObject {
public:
    MyRectangle() : AstrumRectangleObject(AstrumColor::Pink, AstrumColor::Periwinkle, AstrumColor::Lilac, AstrumColor::LightBlue) {
        position.SetX(2.0f);
        position.SetZ(2.0f);
    }

    virtual void Update() override {
        rotation.AddZ(static_cast<float>(AstrumChrono::Instance().GetDeltaTime() * 614));
        AstrumObject::Update();
    }
};
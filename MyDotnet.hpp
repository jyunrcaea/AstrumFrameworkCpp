#pragma once
#include "AstrumMaterialObject.hpp"
#include "AstrumChrono.hpp"

class MyDotnet : public AstrumMaterialObject {
public:
    MyDotnet() : AstrumMaterialObject(
        make_shared<AstrumTexture>(L"./Resource/dotnet.png")
    ) {
        GetPosition().Reset(0.5, 0, 1);
    }

    virtual void Update() override {
        float delta = static_cast<float>(AstrumChrono::Instance().GetDeltaTime());
        float size = static_cast<float>(10 * delta);

        AstrumVector3 movement{};
        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_UP))
            movement.Y++;
        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_DOWN))
            movement.Y--;
        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_LEFT))
            movement.X--;
        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_RIGHT))
            movement.X++;

        movement.Normalize();
        GetPosition() += movement * size;

        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_1))
            GetRotation().AddZ(size * 30);
        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_3))
            GetRotation().AddZ(-size * 30);

        float& opacity = GetMaterial().GetOpacity();
        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_Z)) {
            opacity = min(1.f, opacity + delta);
        }
        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_C)) {
            opacity = max(0.f, opacity - delta);
        }

        AstrumMaterialObject::Update();
    }
};
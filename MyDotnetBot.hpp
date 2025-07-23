#pragma once
#include "AstrumMaterialObject.hpp"
#include "AstrumChrono.hpp"

class MyDotnetBot : public AstrumMaterialObject {
public:
    MyDotnetBot() : AstrumMaterialObject(
        make_shared<AstrumTexture>(L"./Resource/dotnetbot.png")
    ) {
        GetPosition().Reset(-0.5, 0, 1);
    }

    virtual void Update() override {
        float delta = static_cast<float>(AstrumChrono::Instance().GetDeltaTime());
        float size = static_cast<float>(10 * delta);

        AstrumVector3 movement{};
        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_W))
            movement.Y++;
        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_S))
            movement.Y--;
        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_A))
            movement.X--;
        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_D))
            movement.X++;

        movement.Normalize();
        GetPosition() += movement * size;

        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_Q))
            GetRotation().AddZ(size * 30);
        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_E))
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
#pragma once
#include <iostream>
#include "AstrumRectangleObject.hpp"
#include "AstrumColor.hpp"
#include "AstrumOBBColliderComponent.h"

class MyRect2 : public AstrumRectangleObject {
public:
    MyRect2() : AstrumRectangleObject(AstrumColor::LightBlue, AstrumColor::Lilac, AstrumColor::Pink, AstrumColor::Periwinkle) {
        AddComponent(collider = std::make_shared<AstrumOBBColliderComponent>());
        collider->SetOnCollisionEnter(std::bind(&MyRect2::Overlap, this, placeholders::_1));

        position.SetX(1.0f);
        position.SetZ(2.0f);
    }

    virtual void Update() override {
        float size = static_cast<float>(10 * AstrumChrono::Instance().GetDeltaTime());

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
            GetRotation().AddZ(size * 10);
        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_E))
            GetRotation().AddZ(-size * 10);

        AstrumObject::Update();
    }
private:
    shared_ptr<AstrumColliderComponent> collider;

    void Overlap(AstrumColliderComponent* other) {
        std::cout << "overlap!" << std::endl;
    }
};

class MyRect3 : public AstrumRectangleObject {
public:
    MyRect3() : AstrumRectangleObject(AstrumColor::Pink, AstrumColor::Periwinkle, AstrumColor::Lilac, AstrumColor::LightBlue) {
        AddComponent(collider = std::make_shared<AstrumOBBColliderComponent>());
        collider->SetOnCollisionExit(std::bind(&MyRect3::Exit, this, placeholders::_1));

        position.SetX(-1.0f);
        position.SetZ(2.0f);
    }
    virtual void Update() override {
        AstrumVector3 scalar{};
        float size = static_cast<float>(2 * AstrumChrono::Instance().GetDeltaTime());
        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_Z)) {
            scalar.X += size;
            scalar.Y += size;
        }
        if (AstrumDirectInput::Instance().IsKeyPressed(DIK_C)) {
            scalar.X -= size;
            scalar.Y -= size;
        }
        GetScale() += scalar;

        AstrumRectangleObject::Update();
    }
private:
    shared_ptr<AstrumColliderComponent> collider;

    void Exit(AstrumColliderComponent* const other) {
        std::cout << "exit!" << std::endl;
    }
};
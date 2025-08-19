#pragma once
#include "../Vectors/AstrumVector4.hpp"
#include "../Units/AstrumColor.hpp"
#include "../Singletons/AstrumFramework.hpp"
#include "../Singletons/AstrumDirectInput.hpp"
#include "../Objects/AstrumRectangleObject.hpp"
#include "../Components/AstrumStateComponent.hpp"
#include "../Components/AstrumAnimatorComponent.hpp"
#include "../Animations/AstrumMovementAnimator.hpp"
#include "../Animations/AstrumAnimationFunctions.hpp"
#include "../Singletons/AstrumKeyBinder.hpp"

class MyRectObject : public AstrumRectangleObject
{
public:
    MyRectObject() : AstrumRectangleObject(200, 200, AstrumColor::Periwinkle) {
        Position.SetZ(100);

        AddComponent(horizontalAnimator = AstrumAnimatorComponent::MakeShared());
        AddComponent(verticalAnimator = AstrumAnimatorComponent::MakeShared());

        auto horizontalGraph = AstrumStateGraph::MakeShared();
        horizontalGraph->MakeStateBuilder("Idle")
            .AddHoldConditionTwoWay("Left", [this]() { return AstrumKeyBinder::IsKeyPressed("Left"); })
            .AddHoldConditionTwoWay("Right", [this]() { return AstrumKeyBinder::IsKeyPressed("Right"); })
            .SetCallback([this](auto type) { if (type > 0) SetMoveX(0); });
        horizontalGraph->SetCallback("Left", [this](auto type) { if (type > 0) SetMoveX(-300); });
        horizontalGraph->SetCallback("Right", [this](auto type) { if (type > 0) SetMoveX(300); });
        AddComponent(AstrumStateComponent::MakeShared("Idle", horizontalGraph));

        auto verticalGraph = AstrumStateGraph::MakeShared();
        verticalGraph->MakeStateBuilder("Idle")
            .AddHoldConditionTwoWay("Up", [this]() { return AstrumKeyBinder::IsKeyPressed("Up"); })
            .AddHoldConditionTwoWay("Down", [this]() { return AstrumKeyBinder::IsKeyPressed("Down"); })
            .SetCallback([this](auto type) { if (type > 0) SetMoveY(0); });
        verticalGraph->SetCallback("Up", [this](auto type) { if (type > 0) SetMoveY(300); });
        verticalGraph->SetCallback("Down", [this](auto type) { if (type > 0) SetMoveY(-300); });
        AddComponent(AstrumStateComponent::MakeShared("Idle", verticalGraph));
    }

private:
    std::shared_ptr<AstrumAnimatorComponent> horizontalAnimator;
    std::shared_ptr<AstrumAnimatorComponent> verticalAnimator;
    void SetMoveX(float x) {
        auto movement = AstrumMovementAnimator::MakeShared(0.18f, x);
        movement->AnimationFunction = AstrumAnimationFunctions::EaseOutQuad;
        horizontalAnimator->ResetAnimator(movement);
    }
    void SetMoveY(float y) {
        auto movement = AstrumMovementAnimator::MakeShared(0.18f, NAN, y);
        movement->AnimationFunction = AstrumAnimationFunctions::EaseOutQuad;
        verticalAnimator->ResetAnimator(movement);
    }
};

class MyRectCursorObject : public AstrumRectangleObject
{
public:
    MyRectCursorObject() : AstrumRectangleObject(50, 50, AstrumColor::SkyBlue) {
        Position.SetZ(20);
    }

    virtual void Update() override {
        AstrumVector2 halfSize{
            static_cast<float>(AstrumWindow::GetWidth() * 0.5),
            static_cast<float>(AstrumWindow::GetHeight() * 0.5)
        };
        Position.Reset(AstrumDirectInput::GetMousePosition() - halfSize);
        AstrumRectangleObject::Update();
    }
};

class MyKeyStatusGroupObject : public AstrumGroupObject
{
public:
    MyKeyStatusGroupObject() {
        for (auto* key : { &wKey, &aKey, &sKey, &dKey }) {
            *key = AstrumRectangleObject::MakeShared(10, 10, AstrumColor::DarkGray);
        }

        wKey->GetPosition().AddY(15);
        aKey->GetPosition().AddX(-15);
        dKey->GetPosition().AddX(15);

        AddObjects({ wKey, sKey, aKey, dKey });
        Position.Reset(
            AstrumWindow::GetWidth() * -0.4f,
            AstrumWindow::GetHeight() * -0.4f,
            10
        );
    }

    virtual void Update() override {
        if (bool result = AstrumKeyBinder::IsKeyPressed("Up"); wLight != result) {
            wKey->SetColor(result ? AstrumColor::LightBlue : AstrumColor::DarkGray);
            wLight = result;
        }
        if (bool result = AstrumKeyBinder::IsKeyPressed("Left"); aLight != result) {
            aKey->SetColor(result ? AstrumColor::LightBlue : AstrumColor::DarkGray);
            aLight = result;
        }
        if (bool result = AstrumKeyBinder::IsKeyPressed("Down"); sLight != result) {
            sKey->SetColor(result ? AstrumColor::LightBlue : AstrumColor::DarkGray);
            sLight = result;
        }
        if (bool result = AstrumKeyBinder::IsKeyPressed("Right"); dLight != result) {
            dKey->SetColor(result ? AstrumColor::LightBlue : AstrumColor::DarkGray);
            dLight = result;
        }

        AstrumGroupObject::Update();
    }

private:
    std::shared_ptr<AstrumRectangleObject> wKey, aKey, sKey, dKey;
    bool wLight = false, aLight = false, sLight = false, dLight = false;
};

class Program
{
    friend int main();

private:
    void SetupKeyBinding() {
        AstrumKeyBinder::AddKeyBind("Up", DIK_W);
        AstrumKeyBinder::AddKeyBind("Down", DIK_S);
        AstrumKeyBinder::AddKeyBind("Left", DIK_A);
        AstrumKeyBinder::AddKeyBind("Right", DIK_D);

        AstrumKeyBinder::AddKeyBind("Up", DIK_UP);
        AstrumKeyBinder::AddKeyBind("Down", DIK_DOWN);
        AstrumKeyBinder::AddKeyBind("Left", DIK_LEFT);
        AstrumKeyBinder::AddKeyBind("Right", DIK_RIGHT);
    }

    void Main() {
        AstrumFramework::Initialize();
        SetupKeyBinding();
        AstrumFramework::GetRootObject()->AddObjects({
            std::make_shared<MyRectObject>(),
            std::make_shared<MyRectCursorObject>(),
            std::make_shared<MyKeyStatusGroupObject>(),
            });
        AstrumFramework::Run();
    }
};
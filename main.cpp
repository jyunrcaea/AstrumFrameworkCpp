#include <iostream>
#include "Vectors/AstrumVector4.hpp"
#include "Units/AstrumColor.hpp"
#include "Singletons/AstrumFramework.hpp"
#include "Singletons/AstrumDirectInput.hpp"
#include "Objects/AstrumRectangleObject.hpp"
#include "Components/AstrumStateComponent.hpp"
#include "Components/AstrumAnimatorComponent.hpp"
#include "Animations/AstrumMovementAnimator.hpp"
#include "Animations/AstrumAnimationFunctions.hpp"
#include "Singletons/AstrumKeyBinder.hpp"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

class MyRectObject : public AstrumRectangleObject
{
public:
    MyRectObject() : AstrumRectangleObject(200, 200, AstrumColor::Periwinkle) {
        Position.SetZ(100);

        AddComponent(animator = AstrumAnimatorComponent::MakeShared());

        auto graph = AstrumStateGraph::MakeShared();
        graph->AddStateName("LeftTop", [this](auto status) { if (status > 0) SetMoveTarget(-200, 200); });
        graph->AddStateName("RightTop", [this](auto status) { if (status > 0) SetMoveTarget(200, 200); });
        graph->AddStateName("LeftBottom", [this](auto status) { if (status > 0) SetMoveTarget(-200, -200); });
        graph->AddStateName("RightBottom", [this](auto status) { if (status > 0) SetMoveTarget(200, -200); });
        graph->MakeStateBuilder("Idle")
            .SetCallback([this](auto status) { if (status > 0) SetMoveTarget(0, 0); })
            .AddHoldConditionTwoWay("Up", [this]() { return AstrumKeyBinder::IsKeyPressed("Up"); })
            .AddHoldConditionTwoWay("Down", [this]() { return AstrumKeyBinder::IsKeyPressed("Down"); })
            .AddHoldConditionTwoWay("Left", [this]() { return AstrumKeyBinder::IsKeyPressed("Left"); })
            .AddHoldConditionTwoWay("Right", [this]() { return AstrumKeyBinder::IsKeyPressed("Right"); });
        graph->MakeStateBuilder("Left")
            .SetCallback([this](auto status) { if (status > 0) SetMoveTarget(-200, 0); })
            .AddHoldConditionTwoWay("LeftTop", [this]() { return AstrumKeyBinder::IsKeyPressed("Up"); })
            .AddHoldConditionTwoWay("LeftBottom", [this]() { return AstrumKeyBinder::IsKeyPressed("Down"); });
        graph->MakeStateBuilder("Right")
            .SetCallback([this](auto status) { if (status > 0) SetMoveTarget(200, 0); })
            .AddHoldConditionTwoWay("RightTop", [this]() { return AstrumKeyBinder::IsKeyPressed("Up"); })
            .AddHoldConditionTwoWay("RightBottom", [this]() { return AstrumKeyBinder::IsKeyPressed("Down"); });
        graph->MakeStateBuilder("Up")
            .SetCallback([this](auto status) { if (status > 0) SetMoveTarget(0, 200); })
            .AddHoldConditionTwoWay("LeftTop", [this]() { return AstrumKeyBinder::IsKeyPressed("Left"); })
            .AddHoldConditionTwoWay("RightTop", [this]() { return AstrumKeyBinder::IsKeyPressed("Right"); });
        graph->MakeStateBuilder("Down")
            .SetCallback([this](auto status) { if (status > 0) SetMoveTarget(0, -200); })
            .AddHoldConditionTwoWay("LeftBottom", [this]() { return AstrumKeyBinder::IsKeyPressed("Left"); })
            .AddHoldConditionTwoWay("RightBottom", [this]() { return AstrumKeyBinder::IsKeyPressed("Right"); });

        AddComponent(AstrumStateComponent::MakeShared("Idle", graph));
    }

private:
    std::shared_ptr<AstrumAnimatorComponent> animator;
    void SetMoveTarget(float x,float y) {
        auto movement = AstrumMovementAnimator::MakeShared({ x, y }, 0.2f);
        movement->AnimationFunction = AstrumAnimationFunctions::EaseOutQuad;
        animator->ResetAnimator(movement);
    }
};

class MyRectCursorObject : public AstrumRectangleObject {
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
        d Key->GetPosition().AddX(15);

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

int main()
{
#ifdef _DEBUG
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    Program().Main();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    return main();
}
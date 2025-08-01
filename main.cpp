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
        AddComponent(animator = AstrumAnimatorComponent::MakeShared());

        auto graph = AstrumStateGraph::MakeShared();
        graph->AddStateName("LeftTop", [this](auto status) { if (status > 0) SetMoveTarget(-200, 200); });
        graph->AddStateName("RightTop", [this](auto status) { if (status > 0) SetMoveTarget(200, 200); });
        graph->AddStateName("LeftBottom", [this](auto status) { if (status > 0) SetMoveTarget(-200, -200); });
        graph->AddStateName("RightBottom", [this](auto status) { if (status > 0) SetMoveTarget(200, -200); });
        graph->MakeBuilder("Idle")
            .SetCallback([this](auto status) { if (status > 0) SetMoveTarget(0, 0); })
            .AddHoldConditionTwoWay("Up", [this]() { return AstrumKeyBinder::IsKeyPressed("Up"); })
            .AddHoldConditionTwoWay("Down", [this]() { return AstrumKeyBinder::IsKeyPressed("Down"); })
            .AddHoldConditionTwoWay("Left", [this]() { return AstrumKeyBinder::IsKeyPressed("Left"); })
            .AddHoldConditionTwoWay("Right", [this]() { return AstrumKeyBinder::IsKeyPressed("Right"); });
        graph->MakeBuilder("Left")
            .SetCallback([this](auto status) { if (status > 0) SetMoveTarget(-200, 0); })
            .AddHoldConditionTwoWay("LeftTop", [this]() { return AstrumKeyBinder::IsKeyPressed("Up"); })
            .AddHoldConditionTwoWay("LeftBottom", [this]() { return AstrumKeyBinder::IsKeyPressed("Down"); });
        graph->MakeBuilder("Right")
            .SetCallback([this](auto status) { if (status > 0) SetMoveTarget(200, 0); })
            .AddHoldConditionTwoWay("RightTop", [this]() { return AstrumKeyBinder::IsKeyPressed("Up"); })
            .AddHoldConditionTwoWay("RightBottom", [this]() { return AstrumKeyBinder::IsKeyPressed("Down"); });
        graph->MakeBuilder("Up")
            .SetCallback([this](auto status) { if (status > 0) SetMoveTarget(0, 200); })
            .AddHoldConditionTwoWay("LeftTop", [this]() { return AstrumKeyBinder::IsKeyPressed("Left"); })
            .AddHoldConditionTwoWay("RightTop", [this]() { return AstrumKeyBinder::IsKeyPressed("Right"); });
        graph->MakeBuilder("Down")
            .SetCallback([this](auto status) { if (status > 0) SetMoveTarget(0, -200); })
            .AddHoldConditionTwoWay("LeftBottom", [this]() { return AstrumKeyBinder::IsKeyPressed("Left"); })
            .AddHoldConditionTwoWay("RightBottom", [this]() { return AstrumKeyBinder::IsKeyPressed("Right"); });

        AddComponent(AstrumStateComponent::MakeShared("Idle", graph));
    }

    virtual void Update() override {

        AstrumRectangleObject::Update();
    }

private:
    std::shared_ptr<AstrumAnimatorComponent> animator;
    void SetMoveTarget(float x,float y) {
        auto movement = AstrumMovementAnimator::MakeShared({ x, y }, 0.2f);
        movement->AnimationFunction = AstrumAnimationFunctions::EaseOutQuad;
        animator->ResetAnimator(movement);
    }
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
        AstrumFramework::GetRootObject()->AddObject(
            std::make_shared<MyRectObject>()
        );
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
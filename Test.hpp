#pragma once
#include <iostream>
#include <memory>
#include "Framework.hpp"
#include "./AstrumShaderPipeline.hpp"
#include "./AstrumRectangleObject.hpp"
#include "./AstrumTriangleObject.hpp"
#include "./AstrumCircleObject.hpp"
#include "./AstrumAABBColliderComponent.h"
#include "./AstrumCircleColliderComponent.h"
#include "./AstrumOBBColliderComponent.h"
#include "./AstrumImage.hpp"
#include "./AstrumTexture.hpp"
#include "./AstrumMaterialTexture.hpp"

namespace {
    void Logging(const string& name, const AstrumObject* const obj) {
        std::cout << format("{}() : pos {} {} {} scale {} {} {}", name, obj->GetAbsolutePosition().X, obj->GetAbsolutePosition().Y, obj->GetAbsolutePosition().Z, obj->GetAbsoluteScale().X, obj->GetAbsoluteScale().Y, obj->GetAbsoluteScale().Z) << std::endl;
    }
}

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

class MyRect2 : public AstrumRectangleObject {
public:
    MyRect2() : AstrumRectangleObject(AstrumColor::LightBlue, AstrumColor::Lilac, AstrumColor::Pink, AstrumColor::Periwinkle) {
        components.Add(collider = std::make_shared<AstrumOBBColliderComponent>());
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
        components.Add(collider = std::make_shared<AstrumOBBColliderComponent>());
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

class MyObject : public AstrumObject {
public:
    MyObject() {}

    virtual void Update() override {
        if ((time += static_cast<float>(AstrumChrono::Instance().GetDeltaTime())) >= 1) {
            if ((time -= 1) >= 1) time = 0;
            cout << "frame per second: " << count << '\n';
            count = 0;
        }
        count++;
        AstrumObject::Update();
    }

private:
    float time = 0;
    int count = 0;
};

class Test : public Singleton<Test> {
	friend class Singleton<Test>;

    void Prepare() {
        std::cin.tie(0)->sync_with_stdio(0);
        Framework::Instance().Initialize(); // 프레임워크 초기화
        auto pipeline = make_shared<AstrumShaderPipeline>();
        //여기서 셰이더 만들고
        pipeline->VertexShader = make_shared<AstrumVertexShader>(L"./Shaders/ColorMesh.fx", "ColorMeshVS");
        pipeline->PixelShader = make_shared<AstrumPixelShader>(L"./Shaders/ColorMesh.fx", "ColorMeshPS");
        pipeline->AddInputLayoutDescription("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0);
        pipeline->AddInputLayoutDescription("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0);
        //여기서 설정
        AstrumRenderer::Instance().SetDefaultShaderPipeline(pipeline);
    }
public:
    void First() {
        Prepare();

        Framework::Instance().RootObject->GetObjects()->AddRange({
            make_shared<MyRect2>(),
            make_shared<MyRect3>(),
            make_shared<MyObject>()
            });
        Framework::Instance().Run();
    }

    void Second() {
        Prepare();

        Framework::Instance().RootObject->GetObjects()->AddRange({
            make_shared<MyRectangle>(),
            make_shared<MyTriangle>(),
            make_shared<MyCircle>(),
            make_shared<MyObject>()
            });
        Framework::Instance().Run();
    }

    void Three() {
        Prepare();
        AstrumTexture texture(AstrumImage { L"Resource/dotnet.png" });

        Framework::Instance().RootObject->GetObjects()->AddRange({
        });
		Framework::Instance().Run();
    }
};
#pragma once
#include <iostream>
#include <memory>
#include "AstrumFramework.hpp"
#include "AstrumShaderPipeline.hpp"
#include "AstrumPixelShader.hpp"
#include "AstrumDirectInput.hpp"
#include "AstrumChrono.hpp"
#include "AstrumFrameAnimationComponent.hpp"
#include "AstrumTextureManager.hpp"

#include "AstrumMaterialObject.hpp"
#include "AstrumRectangleObject.hpp"
#include "AstrumPolygonsObject.hpp"

#include "MainScene.hpp"
#include "TestScene.hpp"

class MyFrameCounter : public AstrumObject {
public:
    MyFrameCounter() {}

    virtual void Update() override {
        if ((time += static_cast<float>(AstrumChrono::Instance().GetDeltaTime())) >= 1) {
            if ((time -= 1) >= 1) time = 0;
            std::cout << "frame per second: " << count << '\n';
            count = 0;
        }
        count++;
        AstrumObject::Update();
    }

private:
    float time = 0;
    int count = 0;
};

class Program : public Singleton<Program> {
	friend class Singleton<Program>;

    void Prepare() {
        std::cin.tie(0)->sync_with_stdio(0);
        // 프레임워크 초기화
        AstrumFramework::Instance().Initialize();

        // 도형을 위한 셰이더
        auto shapePipeline = AstrumShaderPipeline::MakeShared();
        shapePipeline->VertexShader = AstrumVertexShader::MakeShared(L"./Shaders/ColorMesh.fx", "ColorMeshVS");
        shapePipeline->PixelShader = AstrumPixelShader::MakeShared(L"./Shaders/ColorMesh.fx", "ColorMeshPS");
        shapePipeline->AddInputLayoutDescription("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0);
        shapePipeline->AddInputLayoutDescription("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0);
        AstrumRenderer::Instance().DefaultShapeShaderPipeline = shapePipeline;

        // 텍스쳐를 위한 셰이더
        auto texturePipeline = AstrumShaderPipeline::MakeShared();
        texturePipeline->VertexShader = AstrumVertexShader::MakeShared(L"./Shaders/Mesh.fx", "MeshVS");
        texturePipeline->PixelShader = AstrumPixelShader::MakeShared(L"./Shaders/Mesh.fx", "DefaultMaterialPS");
        texturePipeline->AddInputLayoutDescription("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0);
        texturePipeline->AddInputLayoutDescription("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0);
        AstrumRenderer::Instance().DefaultTextureShaderPipeline = texturePipeline;
    }
public:
    void Main() {
        Prepare();
        //AstrumFramework::Instance().RootObject = std::make_shared<MainScene>();
        AstrumFramework::Instance().RootObject = std::make_shared<TestScene>();
#if _DEBUG
        AstrumFramework::Instance().RootObject->AddObject(std::make_shared<MyFrameCounter>());
#endif
        AstrumFramework::Instance().Run();
    }
};
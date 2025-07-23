#pragma once
#include <iostream>
#include <memory>
#include "AstrumFramework.hpp"
#include "AstrumShaderPipeline.hpp"
#include "AstrumPixelShader.hpp"

#include "MyFrameAnimationObject.hpp"

class Program : public Singleton<Program> {
	friend class Singleton<Program>;

    void Prepare() {
        std::cin.tie(0)->sync_with_stdio(0);
        // 프레임워크 초기화
        AstrumFramework::Instance().Initialize();

        // 도형을 위한 셰이더
        auto shapePipeline = make_shared<AstrumShaderPipeline>();
        shapePipeline->VertexShader = make_shared<AstrumVertexShader>(L"./Shaders/ColorMesh.fx", "ColorMeshVS");
        shapePipeline->PixelShader = make_shared<AstrumPixelShader>(L"./Shaders/ColorMesh.fx", "ColorMeshPS");
        shapePipeline->AddInputLayoutDescription("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0);
        shapePipeline->AddInputLayoutDescription("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0);
        AstrumRenderer::Instance().DefaultShapeShaderPipeline = shapePipeline;

        // 텍스쳐를 위한 셰이더
        auto texturePipeline = make_shared<AstrumShaderPipeline>();
        texturePipeline->VertexShader = make_shared<AstrumVertexShader>(L"./Shaders/Mesh.fx", "MeshVS");
        texturePipeline->PixelShader = make_shared<AstrumPixelShader>(L"./Shaders/Mesh.fx", "DefaultMaterialPS");
        texturePipeline->AddInputLayoutDescription("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0);
        texturePipeline->AddInputLayoutDescription("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0);
        AstrumRenderer::Instance().DefaultTextureShaderPipeline = texturePipeline;
    }
public:
    void Main() {
        Prepare();

        AstrumFramework::Instance().RootObject->AddObject(make_shared< MyFrameAnimationObject>());
        AstrumFramework::Instance().Run();
    }
};
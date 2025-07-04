#include <bits/stdc++.h>
#include "Framework.hpp"
#include "./AstrumShaderPipeline.hpp"
#include "./AstrumRectangleObject.hpp"

int main()
{
    Framework::Instance().Initialize();
    auto pipeline = make_shared<AstrumShaderPipeline>();
    pipeline->VertexShader = make_shared<AstrumVertexShader>(L"./Shaders/ColorMesh.fx", "ColorMeshVS");
    pipeline->PixelShader = make_shared<AstrumPixelShader>(L"./Shaders/ColorMesh.fx", "ColorMeshPS");
    pipeline->AddInputLayoutDescription("POSITION" , 0 , DXGI_FORMAT_R32G32B32_FLOAT , 0);
    pipeline->AddInputLayoutDescription("COLOR" , 0 , DXGI_FORMAT_R32G32B32A32_FLOAT , 0);
    AstrumRenderer::Instance().shaderPipeline = pipeline;

    shared_ptr<IAstrumObject> rect = make_shared<AstrumRectangleObject>(
        AstrumVertexColor(AstrumVector3 {-0.5f , 0.5f, 1} , AstrumColor::Pink) ,
        AstrumVertexColor(AstrumVector3 {0.5f , 0.5f, 1 } , AstrumColor::Periwinkle) ,
        AstrumVertexColor(AstrumVector3 {-0.5f , -0.5f, 1 } , AstrumColor::Lilac) ,
        AstrumVertexColor(AstrumVector3 {0.5f , -0.5f, 1 } , AstrumColor::LightBlue)
    );
    //rect->GetPosition().Z = -5;
    Framework::Instance().RootObject->GetObjects()->Add(rect);
    Framework::Instance().Run();
}
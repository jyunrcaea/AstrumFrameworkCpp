#pragma once
#include <cstring>
#include "AstrumShaderSetup.hpp"

class AstrumDefaultShaders {
public:
    inline static const char* ShapeShaderCode = R"(
struct PS_Output_Single
{
    float4 Color : SV_TARGET;
};

cbuffer Transform : register(b0)
{
    matrix WorldMatrix;
    matrix ViewMatrix;
    matrix ProjectionMatrix;
    matrix WorldViewMatrix;
    matrix WorldViewProjectionMatrix;
}

cbuffer Material : register(b1)
{
    float4 MaterialBaseColor;
    float MaterialOpacity;
    int MaterialTextureWidth;
    int MaterialTextureHeight;
    int MaterialFlip;
}

// 이 값 이하의 알파를 가진 픽셀은 그리지 않으며, 깊이 버퍼에도 기록하지 않습니다. (8비트 기준 1/255)
static const float AlphaClipThreshold = 1.0f / 255.0f;

SamplerState gBaseSample : register(s0);

Texture2D gBaseTexture : register(t0);

struct VS_Input_Color
{
	float3 Pos : POSITION;
	float4 Color : COLOR;
};

struct VS_Output_Color
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

VS_Output_Color ColorMeshVS(VS_Input_Color input)
{
	VS_Output_Color output = (VS_Output_Color) 0;

	output.Pos = mul(float4(input.Pos, 1.f), WorldViewProjectionMatrix);
	output.Color = input.Color;
    
	return output;
}

PS_Output_Single ColorMeshPS(VS_Output_Color input)
{
	PS_Output_Single output = (PS_Output_Single) 0;
    
	float4 color = input.Color;
	
	// 깊이 기록이 켜져 있으므로, 완전히 투명한 픽셀은 버려서 뒤쪽 물체를 가리지 않게 합니다.
	clip(color.a - AlphaClipThreshold);
	
	// 블렌드 상태가 premultiplied alpha(SrcBlend = ONE) 이므로 색상에 알파를 곱합니다.
	color.rgb *= color.a;
    
	output.Color = color;
    
	return output;
}
)";

    inline static const char* MaterialShaderCode = R"(
struct PS_Output_Single
{
    float4 Color : SV_TARGET;
};

cbuffer Transform : register(b0)
{
    matrix WorldMatrix;
    matrix ViewMatrix;
    matrix ProjectionMatrix;
    matrix WorldViewMatrix;
    matrix WorldViewProjectionMatrix;
}

cbuffer Material : register(b1)
{
    float4 MaterialBaseColor;
    float MaterialOpacity;
    int MaterialTextureWidth;
    int MaterialTextureHeight;
    int MaterialFlip;
}

// 이 값 이하의 알파를 가진 픽셀은 그리지 않으며, 깊이 버퍼에도 기록하지 않습니다. (8비트 기준 1/255)
static const float AlphaClipThreshold = 1.0f / 255.0f;

SamplerState gBaseSample : register(s0);

Texture2D gBaseTexture : register(t0);

struct VS_Input_Tex
{
    float3 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VS_Output_Tex
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
};

VS_Output_Tex DefaultMaterialVS(VS_Input_Tex input)
{
    VS_Output_Tex output = (VS_Output_Tex) 0;
    
    output.Pos = mul(float4(input.Pos, 1.f), WorldViewProjectionMatrix);
    output.UV = input.UV;
    
    return output;
}

PS_Output_Single DefaultMaterialPS(VS_Output_Tex input)
{
    PS_Output_Single output = (PS_Output_Single) 0;
    
    if (MaterialFlip & 1)
        input.UV.x = 1 - input.UV.x;
    if (MaterialFlip & 2)
        input.UV.y = 1 - input.UV.y;
    
    float4 color = gBaseTexture.Sample(gBaseSample, input.UV);
    
    color.rgb *= MaterialBaseColor.rgb;
    color.a *= MaterialOpacity;
    
    // 깊이 기록이 켜져 있으므로, 완전히 투명한 픽셀은 버려서 뒤쪽 물체를 가리지 않게 합니다.
    clip(color.a - AlphaClipThreshold);
    
    color.rgb *= color.a;
    
    output.Color = color;
    
    return output;
}
)";

    static std::shared_ptr<AstrumShaderSetup> CreateShapeShaderSetup() {
        auto shapePipeline = AstrumShaderSetup::MakeShared();
        const size_t len = std::strlen(ShapeShaderCode);

        shapePipeline->VertexShader = AstrumVertexShader::MakeShared(ShapeShaderCode, len, "ColorMeshVS");
        shapePipeline->PixelShader = AstrumPixelShader::MakeShared(ShapeShaderCode, len, "ColorMeshPS");
        shapePipeline->AddInputLayoutDescription("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0);
        shapePipeline->AddInputLayoutDescription("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0);

        return shapePipeline;
    }
    static std::shared_ptr<AstrumShaderSetup> CreateMaterialShaderSetup() {
        auto texturePipeline = AstrumShaderSetup::MakeShared();
        const size_t len = std::strlen(MaterialShaderCode);

        texturePipeline->VertexShader = AstrumVertexShader::MakeShared(MaterialShaderCode, len, "DefaultMaterialVS");
        texturePipeline->PixelShader = AstrumPixelShader::MakeShared(MaterialShaderCode, len, "DefaultMaterialPS");
        texturePipeline->AddInputLayoutDescription("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0);
        texturePipeline->AddInputLayoutDescription("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0);

        return texturePipeline;
    }
};

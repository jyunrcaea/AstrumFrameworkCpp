#include "../../Astrum/Shaders/Share.fx"

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

cbuffer IllusionInformation : register(b2)
{
    float WindowWidth;
    float WindowHeight;
    float RotationZ;
    float DistortionStrength;
};

VS_Output_Color IllusionVS(VS_Input_Color input)
{
    VS_Output_Color output = (VS_Output_Color) 0;
    output.Pos = mul(float4(input.Pos, 1.f), WorldViewProjectionMatrix);
    output.Color = input.Color;
    return output;
}

PS_Output_Single IllusionPS(VS_Output_Color input)
{
    PS_Output_Single output = (PS_Output_Single) 0;
    output.Color = input.Color;
    return output;
}
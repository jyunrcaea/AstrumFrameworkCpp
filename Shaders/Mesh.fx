#include "Share.fx"

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

VS_Output_Tex MeshVS(VS_Input_Tex input)
{
    VS_Output_Tex output = (VS_Output_Tex) 0;
    
    output.Pos = mul(float4(input.Pos, 1.f), gmatWVP);
    output.UV = input.UV;
    
    return output;
}

PS_Output_Single DefaultMaterialPS(VS_Output_Tex input)
{
    PS_Output_Single output = (PS_Output_Single) 0;
    
    if (gMtrlFlip & 1)
        input.UV.x = 1 - input.UV.x;
    if (gMtrlFlip & 2)
        input.UV.y = 1 - input.UV.y;
    
    float4 color = gBaseTexture.Sample(gBaseSample, input.UV);
    
    color.rgb *= gMtrlBaseColor.rgb;
    color.a *= gMtrlOpacity;
    
    output.Color = color;
    
    return output;
}
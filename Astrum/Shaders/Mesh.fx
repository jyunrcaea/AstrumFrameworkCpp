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

VS_Output_Tex MeshVS(VS_Input_Tex input)
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
    
    color.rgb *= color.a;
    
    output.Color = color;
    
    return output;
}
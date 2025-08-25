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
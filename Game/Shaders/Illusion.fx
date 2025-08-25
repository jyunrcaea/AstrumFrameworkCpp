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

cbuffer IllusionInformation : register(b2)
{
    float WindowWidth;
    float WindowHeight;
    float RotationZ;
    float DistortionStrength;
};

struct VertexShaderInput
{
    float3 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VertexShaderOutput
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
};

struct PixelShaderOutput
{
    float4 Color : SV_TARGET;
};

SamplerState BaseSampler : register(s0);
Texture2D BaseTexture : register(t0);

VertexShaderOutput IllusionVS(VertexShaderInput input)
{
    VertexShaderOutput output = (VertexShaderOutput) 0;
    
    output.Pos = mul(float4(input.Pos, 1.f), WorldViewProjectionMatrix);
    output.UV = input.UV;
    
    // 클립 공간에서 작업 (-1 ~ +1 범위)
    float normalizedY = output.Pos.y / output.Pos.w; // perspective divide 고려
    float scaleX = 1.0f + normalizedY * DistortionStrength; // 위쪽(+1)이면 팽창
    
    output.Pos.x *= scaleX;
    
    return output;
}

PixelShaderOutput IllusionPS(VertexShaderOutput input)
{
    PixelShaderOutput output = (PixelShaderOutput) 0;
    
    if (MaterialFlip & 1)
        input.UV.x = 1 - input.UV.x;
    if (MaterialFlip & 2)
        input.UV.y = 1 - input.UV.y;
    
    float4 color = BaseTexture.Sample(BaseSampler, input.UV);
    
    color.rgb *= MaterialBaseColor.rgb;
    color.a *= MaterialOpacity;
    
    output.Color = color;
    
    return output;
}
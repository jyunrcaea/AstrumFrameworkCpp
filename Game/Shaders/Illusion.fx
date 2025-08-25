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
    float WindowWidth; // 창 높이
    float WindowHeight; // 창 너비
    float RotationZ;
    float DistortionStrength; // 왜곡 강도 (0 ~ 1, 현재 0.4)
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
    return output;
}

//PixelShaderOutput IllusionPS(VertexShaderOutput input)
//{
//    PixelShaderOutput output = (PixelShaderOutput) 0;
    
//    if (MaterialFlip & 1)
//        input.UV.x = 1 - input.UV.x;
//    if (MaterialFlip & 2)
//        input.UV.y = 1 - input.UV.y;
    
//    float4 color = BaseTexture.Sample(BaseSampler, input.UV);
    
//    color.rgb *= MaterialBaseColor.rgb;
//    color.a *= MaterialOpacity;
    
//    output.Color = color;
    
//    return output;
//}

PixelShaderOutput IllusionPS(VertexShaderOutput input)
{
    PixelShaderOutput output = (PixelShaderOutput) 0;
    float2 uv = input.UV;
    if (MaterialFlip & 1)
        uv.x = 1.0f - uv.x;
    if (MaterialFlip & 2)
        uv.y = 1.0f - uv.y;
   
    float scale = 1.0f - (uv.y - 0.5f) * DistortionStrength;
    float2 distortedUV = float2((uv.x - 0.5f) * scale + 0.5f, uv.y);
    float4 color = BaseTexture.Sample(BaseSampler, distortedUV);
    
    color.rgb *= MaterialBaseColor.rgb;
    color.a *= MaterialOpacity;
    
    output.Color = color;
    
    return output;
}
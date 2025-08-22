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
Texture2DMS<float4> BaseTexture : register(t0);

//VertexShaderOutput IllusionVS(VertexShaderInput input)
//{
//    VertexShaderOutput output = (VertexShaderOutput) 0;
//    output.Pos = mul(float4(input.Pos, 1.f), WorldViewProjectionMatrix);
//    output.UV = input.UV;
//    return output;
//}
VertexShaderOutput IllusionVS(VertexShaderInput input)
{
    VertexShaderOutput output = (VertexShaderOutput) 0;
    
    float3 pos = input.Pos;
    
    // 회전 역변환
    float cosZ = cos(-RotationZ);
    float sinZ = sin(-RotationZ);
    float2 rotatedPos;
    rotatedPos.x = pos.x * cosZ - pos.y * sinZ;
    rotatedPos.y = pos.x * sinZ + pos.y * cosZ;
    
    // Y 좌표를 화면 높이로 정규화 (-1 ~ 1 범위로)
    float normalizedY = (rotatedPos.y / (WindowHeight * 0.5f)) - 1.0f;
    
    // 왜곡 적용
    float scaleX = 1.0f + normalizedY * DistortionStrength;
    rotatedPos.x *= scaleX;
    
    // 다시 회전 적용
    pos.x = rotatedPos.x * cosZ - rotatedPos.y * sinZ;
    pos.y = rotatedPos.x * sinZ + rotatedPos.y * cosZ;
    
    output.Pos = mul(float4(pos, 1.f), WorldViewProjectionMatrix);
    output.UV = input.UV;
    return output;
}

PixelShaderOutput IllusionPS(VertexShaderOutput input)
{
    PixelShaderOutput output = (PixelShaderOutput) 0;
    
    if (MaterialFlip & 1)
        input.UV.x = 1 - input.UV.x;
    if (MaterialFlip & 2)
        input.UV.y = 1 - input.UV.y;
    
    float4 color = BaseTexture.Load(int2(input.UV * float2(MaterialTextureWidth, MaterialTextureHeight)), 0);
    
    color.rgb *= MaterialBaseColor.rgb;
    color.a *= MaterialOpacity;
    
    output.Color = color;
    
    return output;
}
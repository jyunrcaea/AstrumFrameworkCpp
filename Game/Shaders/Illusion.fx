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
    
    // 1. 회전 역변환 (Z축 기준)
    float cosZ = cos(-RotationZ);
    float sinZ = sin(-RotationZ);
    float2 rotatedPos;
    rotatedPos.x = pos.x * cosZ - pos.y * sinZ;
    rotatedPos.y = pos.x * sinZ + pos.y * cosZ;
    
    // 2. 왜곡 적용 (y값에 따른 x 스케일링)
    // y가 클수록 수축, 작을수록 팽창
    float normalizedY = (rotatedPos.y + 1.0f) * 0.5f; // -1~1을 0~1로 정규화
    float scaleX = lerp(1.0f + DistortionStrength, 1.0f - DistortionStrength, normalizedY);
    rotatedPos.x *= scaleX;
    
    // 3. 다시 원래 회전 적용
    cosZ = cos(RotationZ);
    sinZ = sin(RotationZ);
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
    
    float4 color = BaseTexture.Sample(BaseSampler, input.UV);
    
    color.rgb *= MaterialBaseColor.rgb;
    color.a *= MaterialOpacity;
    
    output.Color = color;
    
    return output;
}
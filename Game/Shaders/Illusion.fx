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

    // 1. Y좌표를 화면 비율에 맞춰 정규화합니다. (-1.0 ~ 1.0 범위)
    // 화면 중앙(Y=0)이 0, 화면 상단(Y=WindowHeight/2)이 1, 하단(Y=-WindowHeight/2)이 -1이 됩니다.
    float normalizedY = input.Pos.y / (max(720.f, WindowHeight) / 2.0f);

    // 2. Y좌표에 따라 X축 스케일 값을 계산합니다.
    // normalizedY가 1(상단)일 때 스케일은 (1 - DistortionStrength)가 되어 수축합니다.
    // normalizedY가 -1(하단)일 때 스케일은 (1 + DistortionStrength)가 되어 팽창합니다.
    float scaleX = 1.0f - normalizedY * DistortionStrength;

    // 3. 계산된 스케일 값을 X좌표에 적용합니다.
    float3 modifiedPos = input.Pos;
    modifiedPos.x *= scaleX;

    // 4. 변형된 위치(modifiedPos)를 최종 행렬과 곱하여 클립 공간 좌표로 변환합니다.
    output.Pos = mul(float4(modifiedPos, 1.f), WorldViewProjectionMatrix);
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
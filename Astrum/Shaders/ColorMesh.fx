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
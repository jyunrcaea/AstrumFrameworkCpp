#include "AstrumMaterial.h"

AstrumMaterial::AstrumMaterial()
{
}

AstrumMaterial::~AstrumMaterial()
{
}

void AstrumMaterial::SetSampleType(AstrumTextureSampleType type)
{
	sampleType = type;
}

void AstrumMaterial::SetOpacity(float value)
{
	opacity = max(0.f, min(value, 1.f));
}

void AstrumMaterial::SetBaseColor(const AstrumVector4& color)
{
	baseColor = color;
}

void AstrumMaterial::SetBaseColor(float r, float g, float b, float a)
{
	baseColor.X = r;
	baseColor.Y = g;
	baseColor.Z = b;
	baseColor.W = a;
}

AstrumTextureSampleType AstrumMaterial::GetSampleType() const { return sampleType; }
float AstrumMaterial::GetOpacity() const { return opacity; }
const AstrumVector4& AstrumMaterial::GetBaseColor() const { return baseColor; }

void AstrumMaterial::AddTexture(AstrumTexture* const texutre)
{
}

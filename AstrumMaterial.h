#pragma once
#include "AstrumTexture.hpp"

enum AstrumTextureSampleType {
	Point = 0,
	Linear,
	Anisotropic,
	Count
};

class AstrumMaterial
{
public:
	AstrumMaterial();
	virtual ~AstrumMaterial();

protected:
	AstrumTextureSampleType sampleType = AstrumTextureSampleType::Linear;
	float opacity = 1.f;
	AstrumVector4 baseColor = AstrumVector4(1.f, 1.f, 1.f, 1.f);

	std::vector<AstrumTexture*> textures;
private:
	static ID3D11SamplerState* Samplers[AstrumTextureSampleType::Count];

public:
	void SetSampleType(AstrumTextureSampleType type);
	void SetOpacity(float value);
	void SetBaseColor(const AstrumVector4& color);
	void SetBaseColor(float r, float g, float b, float a = 1.f);

	AstrumTextureSampleType GetSampleType() const;
	float GetOpacity() const;
	const AstrumVector4& GetBaseColor() const;

	void AddTexture(AstrumTexture* const texutre);
};
#pragma once
#include <span>
#include "AstrumConstantBuffer.hpp"
#include "AstrumMaterialData.hpp"
#include "AstrumVector2.hpp"
#include "AstrumTextureSampler.hpp"

class AstrumMaterialConstantBuffer : public AstrumConstantBuffer
{
protected:
	AstrumMaterialData data;
public:
	AstrumMaterialConstantBuffer();

	void SetColor(const AstrumVector4& color);
	void SetOpacity(float opacity);
	void SetSize(unsigned short width, unsigned short height);
	void SetSampleType(AstrumTextureSampleType type);

	AstrumVector4& GetColor();
	float& GetOpacity();
	std::pair<unsigned short, unsigned short> GetSize() const;
	AstrumTextureSampleType& GetSampleType();

	void UpdateBuffer();
};


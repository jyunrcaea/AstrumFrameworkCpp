#pragma once
#include <span>
#include "AstrumConstantBuffer.hpp"
#include "../Data/AstrumMaterialData.hpp"
#include "../Vectors/AstrumVector2.hpp"
#include "../Graphics/AstrumTextureSampler.hpp"

class AstrumMaterialConstantBuffer : public AstrumConstantBuffer
{
protected:
	AstrumMaterialData data;
	AstrumTextureSampleType sampleType = AstrumTextureSampleType::AstrumTextureSampleType_Linear;
public:
	AstrumMaterialConstantBuffer();

	void SetColor(const AstrumVector4& color);
	void SetOpacity(float opacity);
	void SetSize(unsigned short width, unsigned short height);
	void SetSampleType(AstrumTextureSampleType sampleType);
	void SetFlip(AstrumMaterialFlipType flip);

	AstrumVector4& GetColor();
	float& GetOpacity();
	std::pair<unsigned short, unsigned short> GetSize() const;
	AstrumTextureSampleType GetSampleType() const;
	AstrumMaterialFlipType GetFlip() const;

	virtual void UpdateBuffer() override;
};


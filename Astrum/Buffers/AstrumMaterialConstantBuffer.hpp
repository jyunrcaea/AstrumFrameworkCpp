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
	AstrumMaterialConstantBuffer() : AstrumConstantBuffer(sizeof(AstrumMaterialData)) {}

	void SetColor(const AstrumVector4& color) { data.BaseColor = color; }
	void SetOpacity(float opacity) { data.Opacity = opacity; }
	void SetSize(unsigned short width, unsigned short height) { data.Width = width; data.Height = height; }
	void SetSampleType(AstrumTextureSampleType type) { this->sampleType = type; }
	void SetFlip(AstrumMaterialFlipType flip) { data.Flip = flip; }

	AstrumVector4& GetColor() { return data.BaseColor; }
	float& GetOpacity() { return data.Opacity; }
	std::pair<unsigned short, unsigned short> GetSize() const { return { static_cast<unsigned short>(data.Width), static_cast<unsigned short>(data.Height) }; }
	AstrumTextureSampleType GetSampleType() const { return sampleType; }
	AstrumMaterialFlipType GetFlip() const { return data.Flip; }

	virtual void UpdateBuffer() override;
};


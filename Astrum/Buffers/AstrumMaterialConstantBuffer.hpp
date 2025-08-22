#pragma once
#include <span>
#include "AstrumConstantBuffer.hpp"
#include "../Data/AstrumMaterialData.hpp"
#include "../Vectors/AstrumVector2.hpp"
#include "../Graphics/AstrumTextureSampler.hpp"

namespace Astrum {
	class MaterialConstantBuffer : public ConstantBuffer
	{
	protected:
		MaterialData data;
		TextureSampleType sampleType = TextureSampleType::TextureSampleType_Linear;
	public:
		MaterialConstantBuffer() : ConstantBuffer(sizeof(MaterialData)) {}

		void SetColor(const Vector4& color) { data.BaseColor = color; }
		void SetOpacity(float opacity) { data.Opacity = opacity; }
		void SetSize(unsigned short width, unsigned short height) { data.Width = width; data.Height = height; }
		void SetSampleType(TextureSampleType type) { this->sampleType = type; }
		void SetFlip(MaterialFlipType flip) { data.Flip = flip; }

		Vector4& GetColor() { return data.BaseColor; }
		float& GetOpacity() { return data.Opacity; }
		std::pair<unsigned short, unsigned short> GetSize() const { return { static_cast<unsigned short>(data.Width), static_cast<unsigned short>(data.Height) }; }
		TextureSampleType GetSampleType() const { return sampleType; }
		MaterialFlipType GetFlip() const { return data.Flip; }

		virtual void UpdateBuffer() override;
	};
}


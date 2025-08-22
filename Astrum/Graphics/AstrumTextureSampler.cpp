#include "AstrumTextureSampler.hpp"
#include "../Singletons/AstrumRenderer.hpp"

namespace Astrum
{
	TextureSampler::TextureSampler() { }
	TextureSampler::~TextureSampler() { }

	void TextureSampler::Initialize() {
		D3D11_SAMPLER_DESC samplerDescription{};
		samplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescription.MinLOD = -FLT_MAX;
		samplerDescription.MaxLOD = FLT_MAX;

		samplerDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		if (FAILED(Renderer::Instance().GetDevice()->CreateSamplerState(&samplerDescription, samplers[TextureSampleType::TextureSampleType_Point].GetAddressOf()))) {
			samplers[TextureSampleType::TextureSampleType_Point] = nullptr;
		}
		samplerDescription.Filter = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		if (FAILED(Renderer::Instance().GetDevice()->CreateSamplerState(&samplerDescription, samplers[TextureSampleType::TextureSampleType_Linear].GetAddressOf()))) {
			samplers[TextureSampleType::TextureSampleType_Linear] = nullptr;
		}
		samplerDescription.Filter = D3D11_FILTER_ANISOTROPIC;
		if (FAILED(Renderer::Instance().GetDevice()->CreateSamplerState(&samplerDescription, samplers[TextureSampleType::TextureSampleType_Anisotropic].GetAddressOf()))) {
			samplers[TextureSampleType::TextureSampleType_Anisotropic] = nullptr;
		}
	}

	void TextureSampler::Dispose() {
		// managed by ComPtr.
	}

	ID3D11SamplerState* const TextureSampler::GetSampler(TextureSampleType type) const
	{
		return samplers[type].Get();
	}

	bool TextureSampler::SetSampler(TextureSampleType type)
	{
		auto sampler = GetSampler(type);
		if (sampler) {
			Renderer::Instance().GetContext()->PSSetSamplers(0, 1, &sampler);
			return true;
		}
		return false;
	}
}
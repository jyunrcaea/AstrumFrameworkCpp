#include "AstrumTextureSampler.hpp"

AstrumTextureSampler::AstrumTextureSampler() { }
AstrumTextureSampler::~AstrumTextureSampler() { }

void AstrumTextureSampler::Initialize() {
	D3D11_SAMPLER_DESC samplerDescription{};
	samplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescription.MinLOD = -FLT_MAX;
	samplerDescription.MaxLOD = FLT_MAX;

	samplerDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	if (FAILED(AstrumRenderer::Instance().GetDevice()->CreateSamplerState(&samplerDescription, samplers[AstrumTextureSampleType::AstrumTextureSampleType_Point].GetAddressOf()))) {
		samplers[AstrumTextureSampleType::AstrumTextureSampleType_Point] = nullptr;
	}
	samplerDescription.Filter = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
	if (FAILED(AstrumRenderer::Instance().GetDevice()->CreateSamplerState(&samplerDescription, samplers[AstrumTextureSampleType::AstrumTextureSampleType_Linear].GetAddressOf()))) {
		samplers[AstrumTextureSampleType::AstrumTextureSampleType_Linear] = nullptr;
	}
	samplerDescription.Filter = D3D11_FILTER_ANISOTROPIC;
	if (FAILED(AstrumRenderer::Instance().GetDevice()->CreateSamplerState(&samplerDescription, samplers[AstrumTextureSampleType::AstrumTextureSampleType_Anisotropic].GetAddressOf()))) {
		samplers[AstrumTextureSampleType::AstrumTextureSampleType_Anisotropic] = nullptr;
	}
}

void AstrumTextureSampler::Dispose() {/*managed by ComPtr.*/ }

ID3D11SamplerState* const AstrumTextureSampler::GetSampler(AstrumTextureSampleType type) const
{
	return samplers[type].Get();
}

bool AstrumTextureSampler::SetSampler(AstrumTextureSampleType type)
{
	auto sampler = GetSampler(type);
	if (sampler) {
		AstrumRenderer::Instance().GetContext()->PSSetSamplers(0, 1, &sampler);
		return true;
	}
	return false;
}
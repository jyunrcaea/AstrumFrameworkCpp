#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "../Singletons/AstrumSingleton.hpp"
#include "../Singletons/AstrumRenderer.hpp"

enum AstrumTextureSampleType {
	AstrumTextureSampleType_Point = 0,
	AstrumTextureSampleType_Linear,
	AstrumTextureSampleType_Anisotropic,
	AstrumTextureSampleType_Count
};

class AstrumTextureSampler : public AstrumSingleton<AstrumTextureSampler>
{
	friend class AstrumSingleton<AstrumTextureSampler>;

public:
	AstrumTextureSampler();
	virtual ~AstrumTextureSampler();

	void Initialize();
	void Dispose();

	ID3D11SamplerState* const GetSampler(AstrumTextureSampleType type) const;
	bool SetSampler(AstrumTextureSampleType type);
private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplers[AstrumTextureSampleType::AstrumTextureSampleType_Count];
};
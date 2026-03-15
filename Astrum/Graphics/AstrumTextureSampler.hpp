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

class AstrumTextureSamplerSingleton : public AstrumSingleton<AstrumTextureSamplerSingleton>
{
	friend class AstrumSingleton<AstrumTextureSamplerSingleton>;
	friend class AstrumTextureSampler;

public:
	AstrumTextureSamplerSingleton();
	virtual ~AstrumTextureSamplerSingleton();

private:

	void Initialize();
	void Dispose();

	ID3D11SamplerState* const GetSampler(AstrumTextureSampleType type) const;
	bool SetSampler(AstrumTextureSampleType type);

private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplers[AstrumTextureSampleType::AstrumTextureSampleType_Count];
};

class AstrumTextureSampler {
public:
	static inline void Initialize() { AstrumTextureSamplerSingleton::Instance().Initialize(); }
	static inline void Dispose() { AstrumTextureSamplerSingleton::Instance().Dispose(); }
	static inline ID3D11SamplerState* const GetSampler(AstrumTextureSampleType type) { return AstrumTextureSamplerSingleton::Instance().GetSampler(type);  }
	static inline bool SetSampler(AstrumTextureSampleType type) { return AstrumTextureSamplerSingleton::Instance().SetSampler(type); }
};
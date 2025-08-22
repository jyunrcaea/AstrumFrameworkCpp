#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "../Singletons/AstrumSingleton.hpp"

namespace Astrum
{
	enum TextureSampleType {
		TextureSampleType_Point = 0,
		TextureSampleType_Linear,
		TextureSampleType_Anisotropic,
		TextureSampleType_Count
	};

	class TextureSampler : public Singleton<TextureSampler>
	{
		friend class Singleton<TextureSampler>;

	public:
		TextureSampler();
		virtual ~TextureSampler();

		void Initialize();
		void Dispose();

		ID3D11SamplerState* const GetSampler(TextureSampleType type) const;
		bool SetSampler(TextureSampleType type);
	private:
		Microsoft::WRL::ComPtr<ID3D11SamplerState> samplers[TextureSampleType::TextureSampleType_Count];
	};
}
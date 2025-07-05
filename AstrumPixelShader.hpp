#pragma once
#include "AstrumShader.hpp"
#include "IAstrumShaders.hpp"
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class AstrumPixelShader : public AstrumShader,
	public IAstrumPixelShader,
	public IAstrumConfigurableShader
{
public:
	AstrumPixelShader(const std::wstring& path,
		const std::string& entryPoint,
		const std::string& profile = "ps_5_0");

	void SetShader() override;

	ID3D11PixelShader* GetPixelShader() const override {
		return shader.Get();
	}

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> shader;
};
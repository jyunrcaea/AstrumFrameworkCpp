#pragma once
#include "AstrumShader.hpp"
#include "IAstrumShaders.hpp"
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class AstrumHullShader : public AstrumShader,
	public IAstrumHullShader,
	public IAstrumConfigurableShader
{
public:
	AstrumHullShader(const std::wstring& path,
		const std::string& entryPoint,
		const std::string& profile = "hs_5_0");

	void SetShader() override;

	ID3D11HullShader* GetHullShader() const override {
		return shader.Get();
	}

private:
	Microsoft::WRL::ComPtr<ID3D11HullShader> shader;
};
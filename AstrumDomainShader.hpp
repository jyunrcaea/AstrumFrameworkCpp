#pragma once
#include "AstrumShader.hpp"
#include "IAstrumShaders.hpp"
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class AstrumDomainShader : public AstrumShader,
	public IAstrumDomainShader,
	public IAstrumConfigurableShader
{
public:
	AstrumDomainShader(const std::wstring& path,
		const std::string& entryPoint,
		const std::string& profile = "ds_5_0");

	void SetShader() override;

	ID3D11DomainShader* GetDomainShader() const override {
		return shader.Get();
	}

private:
	Microsoft::WRL::ComPtr<ID3D11DomainShader> shader;
};
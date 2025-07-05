#pragma once
#include "AstrumShader.hpp"
#include "IAstrumShaders.hpp"
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class AstrumVertexShader : public AstrumShader,
	public IAstrumVertexShader,
	public IAstrumConfigurableShader
{
public:
	AstrumVertexShader(const std::wstring& path,
		const std::string& entryPoint,
		const std::string& profile = "vs_5_0");

	void SetShader() override;

	ID3D11VertexShader* GetVertexShader() const override {
		return shader.Get();
	}

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> shader;
};
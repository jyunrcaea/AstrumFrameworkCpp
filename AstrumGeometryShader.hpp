#pragma once
#include "AstrumShader.hpp"
#include "IAstrumShaders.hpp"
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class AstrumGeometryShader : public AstrumShader,
	public IAstrumGeometryShader,
	public IAstrumConfigurableShader
{
public:
	AstrumGeometryShader(const std::wstring& path,
		const std::string& entryPoint,
		const std::string& profile = "gs_5_0");

	void SetShader() override;

	ID3D11GeometryShader* GetGeometryShader() const override {
		return shader.Get();
	}

private:
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> shader;
};
#pragma once
#include "../AstrumException.hpp"
#include <d3dcompiler.h>
#include <string>
#include <format>
#include <wrl/client.h>

class AstrumShader {
protected:
	AstrumShader(const std::wstring& path, const std::string& entryPoint, const std::string& profile);
	
	Microsoft::WRL::ComPtr<ID3DBlob> blob;

public:
	virtual ~AstrumShader() = default;
	ID3DBlob* GetShaderBlob() const { return blob.Get(); }
};
#pragma once
#include "../AstrumException.hpp"
#include <d3dcompiler.h>
#include <string>
#include <format>
#include <filesystem>
#include <wrl/client.h>

class AstrumShader {
protected:
	AstrumShader(const std::filesystem::path& path, const std::string& entryPoint, const std::string& profile);
	AstrumShader(const char* shaderCode, size_t shaderCodeLength, const std::string& entryPoint, const std::string& profile);
	
	Microsoft::WRL::ComPtr<ID3DBlob> blob;

	bool IsValid() const noexcept { return blob != nullptr; }
	operator bool() const noexcept { return IsValid(); }

public:
	virtual ~AstrumShader() = default;
	ID3DBlob* GetShaderBlob() const { return blob.Get(); }
};
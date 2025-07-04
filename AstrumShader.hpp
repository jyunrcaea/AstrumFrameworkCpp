#pragma once
#include "AstrumException.hpp"
#include <d3dcompiler.h>
#include <string>
#include <wrl/client.h>

using namespace std;

class AstrumShader {
protected:
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	
	AstrumShader(const wstring& path, const string& entryPoint, const string& profile);

public:
	virtual ~AstrumShader() = default;
	ID3DBlob* GetShaderBlob() const { return blob.Get(); }
};
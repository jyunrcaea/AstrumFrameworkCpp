#include "AstrumShader.hpp"

AstrumShader::AstrumShader(const wstring& path, const string& entryPoint, const string& profile) {
	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;
	if (FAILED(D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint.c_str(), profile.c_str(), flags, 0,
		&blob, &errorBlob)))
	{
		if (errorBlob) {
			string err(reinterpret_cast<char*>(errorBlob->GetBufferPointer()), errorBlob->GetBufferSize());
			throw AstrumException("Shader compilation error: " + err);
		}
		throw AstrumException("Failed to compile shader from: " + string(path.begin(), path.end()));
	}
}
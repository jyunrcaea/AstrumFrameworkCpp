#pragma once
#include <d3d11.h>

struct IAstrumTexture
{
public:
	virtual ID3D11ShaderResourceView* GetShaderResourceView() const = 0;
	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;
};
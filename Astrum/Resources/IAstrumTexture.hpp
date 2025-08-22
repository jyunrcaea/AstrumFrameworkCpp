#pragma once
#include <d3d11.h>

namespace Astrum
{
	struct ITexture
	{
	public:
		virtual ID3D11ShaderResourceView* GetShaderResourceView() const = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
	};
}
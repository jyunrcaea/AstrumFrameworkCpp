#pragma once
#include <vector>
#include <string>
#include <memory>
#include <d3d11.h>
#include <dxgi.h>
#include <wrl/client.h>
#include "../Singletons/AstrumRenderer.hpp"
#include "../AstrumException.hpp"
#include "AstrumVertexShader.hpp"
#include "AstrumPixelShader.hpp"
#include "AstrumHullShader.hpp"
#include "AstrumDomainShader.hpp"
#include "AstrumGeometryShader.hpp"

using Microsoft::WRL::ComPtr;

namespace Astrum
{
	class VertexShader;
	class PixelShader;
	class HullShader;
	class DomainShader;
	class GeometryShader;

	class ShaderSetup : public IShaderSetup {
	public:
		ShaderSetup();
		virtual ~ShaderSetup() override;

		std::shared_ptr<VertexShader> VertexShader;
		std::shared_ptr<PixelShader> PixelShader;
		std::shared_ptr<HullShader> HullShader;
		std::shared_ptr<DomainShader> DomainShader;
		std::shared_ptr<GeometryShader> GeometryShader;

		// 여기서 입력 레이아웃을 추가할수 있고
		void AddInputLayoutDescription(
			const std::string& semanticName,
			UINT semanticIndex,
			DXGI_FORMAT format,
			UINT inputSlot,
			D3D11_INPUT_CLASSIFICATION classification = D3D11_INPUT_PER_VERTEX_DATA,
			UINT instanceDataStepRate = 0);
		void SetShader() override;

	private:
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputDescriptions;
		std::vector<char*> semanticNames;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;

	public:
		static inline std::shared_ptr<ShaderSetup> MakeShared() { return std::make_shared<ShaderSetup>(); }
	};
}
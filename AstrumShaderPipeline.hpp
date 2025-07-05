#pragma once
#include <bits/stdc++.h>
#include <d3d11.h>
#include <dxgi.h>
#include <wrl/client.h>
#include "AstrumRenderer.hpp"
#include "AstrumException.hpp"
#include "AstrumVertexShader.hpp"
#include "AstrumPixelShader.hpp"
#include "AstrumHullShader.hpp"
#include "AstrumDomainShader.hpp"
#include "AstrumGeometryShader.hpp"

using Microsoft::WRL::ComPtr;

class AstrumShaderPipeline {
public:
    std::shared_ptr<AstrumVertexShader> VertexShader;
    std::shared_ptr<AstrumPixelShader> PixelShader;
    std::shared_ptr<AstrumHullShader> HullShader;
    std::shared_ptr<AstrumDomainShader> DomainShader;
    std::shared_ptr<AstrumGeometryShader> GeometryShader;

    void AddInputLayoutDescription(
        const std::string& semanticName,
        UINT semanticIndex,
        DXGI_FORMAT format,
        UINT inputSlot,
        D3D11_INPUT_CLASSIFICATION classification = D3D11_INPUT_PER_VERTEX_DATA,
        UINT instanceDataStepRate = 0);
    void SetShader();
    ~AstrumShaderPipeline();

private:
    std::vector<D3D11_INPUT_ELEMENT_DESC> inputDescriptions;
    std::vector<char*> semanticNames;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
};
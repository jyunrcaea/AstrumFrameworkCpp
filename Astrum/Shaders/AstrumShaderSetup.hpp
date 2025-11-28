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

class AstrumShaderSetup : public IAstrumShaderSetup {
public:
    /// <summary>
    /// AstrumShaderSetup 객체를 생성합니다.
    /// </summary>
    AstrumShaderSetup();
    /// <summary>
    /// AstrumShaderSetup 객체를 소멸합니다.
    /// </summary>
    virtual ~AstrumShaderSetup() override;

    /// <summary>
    /// 정점 셰이더입니다.
    /// </summary>
    std::shared_ptr<AstrumVertexShader> VertexShader;
    /// <summary>
    /// 픽셀 셰이더입니다.
    /// </summary>
    std::shared_ptr<AstrumPixelShader> PixelShader;
    /// <summary>
    /// 헐 셰이더입니다.
    /// </summary>
    std::shared_ptr<AstrumHullShader> HullShader;
    /// <summary>
    /// 도메인 셰이더입니다.
    /// </summary>
    std::shared_ptr<AstrumDomainShader> DomainShader;
    /// <summary>
    /// 기하 셰이더입니다.
    /// </summary>
    std::shared_ptr<AstrumGeometryShader> GeometryShader;

    /// <summary>
    /// 정점 입력 레이아웃에 새로운 요소를 추가합니다.
    /// </summary>
    /// <param name="semanticName">입력 요소의 의미론적 이름입니다. (예: "POSITION", "COLOR" 등)</param>
    /// <param name="semanticIndex">같은 이름을 가진 여러 입력 요소를 구분하는 인덱스입니다.</param>
    /// <param name="format">입력 요소의 데이터 형식입니다.</param>
    /// <param name="inputSlot">입력 요소를 받을 입력 슬롯 번호입니다.</param>
    /// <param name="classification">입력 데이터 분류입니다. 기본값은 D3D11_INPUT_PER_VERTEX_DATA입니다.</param>
    /// <param name="instanceDataStepRate">인스턴스 데이터의 스텝 레이트입니다. 기본값은 0입니다.</param>
    void AddInputLayoutDescription(
        const std::string& semanticName,
        UINT semanticIndex,
        DXGI_FORMAT format,
        UINT inputSlot,
        D3D11_INPUT_CLASSIFICATION classification = D3D11_INPUT_PER_VERTEX_DATA,
        UINT instanceDataStepRate = 0);
    /// <summary>
    /// 설정된 셰이더 파이프라인을 렌더링 파이프라인에 적용합니다.
    /// </summary>
    void SetShader() override;

private:
    std::vector<D3D11_INPUT_ELEMENT_DESC> inputDescriptions;
    std::vector<char*> semanticNames;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;

public:
    /// <summary>
    /// AstrumShaderSetup 객체의 공유 포인터를 생성합니다.
    /// </summary>
    /// <returns>새로 생성된 AstrumShaderSetup 공유 포인터입니다.</returns>
    static inline std::shared_ptr<AstrumShaderSetup> MakeShared() { return std::make_shared<AstrumShaderSetup>(); }
};
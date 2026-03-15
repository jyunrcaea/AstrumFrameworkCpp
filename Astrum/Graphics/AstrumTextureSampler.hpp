#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "../Singletons/AstrumSingleton.hpp"
#include "../Singletons/AstrumRenderer.hpp"

/// <summary>
/// 텍스처 샘플링 방식을 나타내는 열거형입니다.
/// Direct3D 렌더링 시 텍스처를 읽을 때 사용되는 필터링 방식을 정의합니다.
/// </summary>
enum AstrumTextureSampleType {
	/// <summary>
	/// 포인트 샘플링입니다. 가장 가까운 텍셀을 선택합니다.
	/// 빠르지만 텍스처가 블록 모양으로 보일 수 있습니다.
	/// </summary>
	AstrumTextureSampleType_Point = 0,
	/// <summary>
	/// 선형 샘플링입니다. 인접한 4개 텍셀을 선형 보간합니다.
	/// 부드러운 결과를 제공하며 일반적으로 사용됩니다.
	/// </summary>
	AstrumTextureSampleType_Linear,
	/// <summary>
	/// 이방성 샘플링입니다. 비스듬한 각도에서 고품질 필터링을 수행합니다.
	/// 가장 높은 품질이지만 가장 비용이 많이 듭니다.
	/// </summary>
	AstrumTextureSampleType_Anisotropic,
	/// <summary>
	/// 샘플링 유형의 개수입니다. (열거형 끝 표시)
	/// </summary>
	AstrumTextureSampleType_Count
};

/// <summary>
/// Direct3D 텍스처 샘플러 상태를 관리하는 싱글톤 클래스입니다.
/// 다양한 필터링 방식의 샘플러를 생성하고 관리합니다.
/// </summary>
class AstrumTextureSamplerSingleton : public AstrumSingleton<AstrumTextureSamplerSingleton>
{
	friend class AstrumSingleton<AstrumTextureSamplerSingleton>;
	friend class AstrumTextureSampler;

public:
	AstrumTextureSamplerSingleton();
	virtual ~AstrumTextureSamplerSingleton();

private:

	/// <summary>
	/// 텍스처 샘플러를 초기화합니다.
	/// 모든 샘플링 방식의 Direct3D 샘플러 상태를 생성합니다.
	/// </summary>
	void Initialize();
	/// <summary>
	/// 텍스처 샘플러를 정리합니다.
	/// 생성된 모든 샘플러 상태 리소스를 해제합니다.
	/// </summary>
	void Dispose();

	/// <summary>
	/// 지정된 샘플링 방식의 Direct3D 샘플러 상태를 반환합니다.
	/// </summary>
	/// <param name="type">원하는 샘플링 방식입니다.</param>
	/// <returns>해당 샘플링 방식의 Direct3D 샘플러 상태 포인터입니다.</returns>
	ID3D11SamplerState* const GetSampler(AstrumTextureSampleType type) const;
	/// <summary>
	/// 렌더링 파이프라인에 지정된 샘플링 방식의 샘플러를 설정합니다.
	/// </summary>
	/// <param name="type">설정할 샘플링 방식입니다.</param>
	/// <returns>성공하면 true, 실패하면 false를 반환합니다.</returns>
	bool SetSampler(AstrumTextureSampleType type);

private:
	/// <summary>
	/// 각 샘플링 방식별 Direct3D 샘플러 상태 배열입니다.
	/// 포인트, 선형, 이방성 샘플러가 저장됩니다.
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplers[AstrumTextureSampleType::AstrumTextureSampleType_Count];
};

class AstrumTextureSampler {
public:
	static inline void Initialize() { AstrumTextureSamplerSingleton::Instance().Initialize(); }
	static inline void Dispose() { AstrumTextureSamplerSingleton::Instance().Dispose(); }
	static inline ID3D11SamplerState* const GetSampler(AstrumTextureSampleType type) { return AstrumTextureSamplerSingleton::Instance().GetSampler(type);  }
	static inline bool SetSampler(AstrumTextureSampleType type) { return AstrumTextureSamplerSingleton::Instance().SetSampler(type); }
};
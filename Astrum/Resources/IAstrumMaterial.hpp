#pragma once
#include <memory>
#include "IAstrumTexture.hpp"
#include "../Meshes/AstrumTextureMesh.hpp"
#include "../Shaders/IAstrumShaders.hpp"

class AstrumTextureMesh;

	/// <summary>
	/// 재질 정보를 관리하는 인터페이스입니다.
	/// </summary>
class IAstrumMaterial
{
	using uint = unsigned int;

public:
	/// <summary>
	/// IAstrumMaterial 인터페이스를 소멸합니다.
	/// </summary>
	virtual ~IAstrumMaterial() = default;

	/// <summary>
	/// 사용자 정의 셰이더 파이프라인을 반환합니다.
	/// </summary>
	/// <returns>사용자 정의 셰이더 파이프라인입니다.</returns>
	virtual std::shared_ptr<IAstrumShaderSetup> GetCustomShaderPipeline() const = 0;
	/// <summary>
	/// 재질의 텍스처를 반환합니다.
	/// </summary>
	/// <returns>재질의 텍스처입니다.</returns>
	virtual std::shared_ptr<IAstrumTexture> GetTexture() const = 0;

	/// <summary>
	/// 재질의 텍스처를 설정합니다.
	/// </summary>
	/// <param name="newTexture">설정할 새로운 텍스처입니다.</param>
	virtual void SetTexture(const std::shared_ptr<IAstrumTexture>& newTexture) = 0;

	/// <summary>
	/// 텍스처의 너비를 반환합니다.
	/// </summary>
	/// <returns>텍스처의 너비(픽셀)입니다.</returns>
	unsigned int GetTextureWidth() const { return GetTexture()->GetWidth(); }
	/// <summary>
	/// 텍스처의 높이를 반환합니다.
	/// </summary>
	/// <returns>텍스처의 높이(픽셀)입니다.</returns>
	unsigned int GetTextureHeight() const { return GetTexture()->GetHeight(); }

	/// <summary>
	/// 텍스처 원본 크기에 맞는 메시를 생성합니다.
	/// </summary>
	/// <param name="z">메시의 Z 깊이 값입니다. 기본값은 0.0f입니다.</param>
	/// <returns>생성된 텍스처 크기 메시입니다.</returns>
	std::shared_ptr<AstrumTextureMesh> CreateTextureSizeMesh(float z = 0.0f) const { return GetTexture()->CreateTextureSizeMesh(z); }
	/// <summary>
	/// 텍스처에서 지정된 영역만 가져오는 메시를 생성합니다.
	/// </summary>
	/// <param name="left">영역의 좌측 위치(픽셀)입니다.</param>
	/// <param name="top">영역의 상측 위치(픽셀)입니다.</param>
	/// <param name="width">영역의 너비(픽셀)입니다.</param>
	/// <param name="height">영역의 높이(픽셀)입니다.</param>
	/// <param name="z">메시의 Z 깊이 값입니다. 기본값은 0입니다.</param>
	/// <returns>생성된 사용자 정의 크기 메시입니다.</returns>
	std::shared_ptr<AstrumTextureMesh> CreateCustomSizeMesh(uint left, uint top, uint width, uint height, float z = 0) const;
	/// <summary>
	/// 텍스처에서 비율을 기반으로 지정된 영역만 가져오는 메시를 생성합니다.
	/// 텍스처 좌표 기준은 왼쪽 위가 (0.0, 0.0), 오른쪽 아래가 (1.0, 1.0)입니다.
	/// </summary>
	/// <param name="left">좌측 텍스처 좌표(0.0~1.0)입니다.</param>
	/// <param name="top">상측 텍스처 좌표(0.0~1.0)입니다.</param>
	/// <param name="right">우측 텍스처 좌표(0.0~1.0)입니다.</param>
	/// <param name="bottom">하측 텍스처 좌표(0.0~1.0)입니다.</param>
	/// <param name="z">메시의 Z 깊이 값입니다. 기본값은 0입니다.</param>
	/// <returns>생성된 비율 기반 메시입니다.</returns>
	std::shared_ptr<AstrumTextureMesh> CreateCustomSizeMeshFromRatio(float left, float top, float right, float bottom, float z = 0) const;
};
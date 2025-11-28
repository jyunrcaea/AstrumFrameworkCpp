#pragma once
#include <string>
#include <memory>
#include "../Buffers/AstrumMaterialConstantBuffer.hpp"
#include "../Graphics/AstrumTextureSampler.hpp"
#include "../Shaders/IAstrumShaders.hpp"
#include "IAstrumMaterial.hpp"
#include "IAstrumTexture.hpp"

class IAstrumMaterial;

/// <summary>
/// 재질을 관리하는 클래스입니다. 텍스처, 색상, 불투명도 등의 재질 속성을 포함합니다.
/// </summary>
class AstrumMaterial : public AstrumMaterialConstantBuffer, public IAstrumMaterial
{
public:
	/// <summary>
	/// 이미지 파일 경로로부터 재질을 생성합니다.
	/// </summary>
	/// <param name="path">로드할 이미지 파일의 경로입니다.</param>
	AstrumMaterial(const std::wstring& path);
	/// <summary>
	/// 텍스처 객체로부터 재질을 생성합니다.
	/// </summary>
	/// <param name="texture">설정할 텍스처입니다.</param>
	AstrumMaterial(const std::shared_ptr<IAstrumTexture>& texture);
	/// <summary>
	/// 텍스처 객체로부터 재질을 생성합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="texture">설정할 텍스처입니다.</param>
	AstrumMaterial(std::shared_ptr<IAstrumTexture>&& texture);

	/// <summary>
	/// 사용자 정의 셰이더 파이프라인입니다. 재질 렌더링 시 기본 셰이더 대신 사용됩니다.
	/// </summary>
	std::shared_ptr<struct IAstrumShaderSetup> CustomShaderPipeline = nullptr;
	/// <summary>
	/// 재질의 텍스처를 반환합니다.
	/// </summary>
	/// <returns>재질의 텍스처입니다.</returns>
	virtual std::shared_ptr<IAstrumTexture> GetTexture() const override { return texture; }
	/// <summary>
	/// 재질의 텍스처를 설정합니다.
	/// </summary>
	/// <param name="newTexture">설정할 새로운 텍스처입니다.</param>
	virtual void SetTexture(const std::shared_ptr<IAstrumTexture>& newTexture) override;
	/// <summary>
	/// 재질의 텍스처를 설정합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="newTexture">설정할 새로운 텍스처입니다.</param>
	void SetTexture(std::shared_ptr<IAstrumTexture>&& newTexture);

private:
	/// <summary>
	/// 사용자 정의 셰이더 파이프라인을 반환합니다.
	/// </summary>
	/// <returns>사용자 정의 셰이더 파이프라인입니다.</returns>
	virtual std::shared_ptr<struct IAstrumShaderSetup> GetCustomShaderPipeline() const override { return CustomShaderPipeline; }
	/// <summary>
	/// 재질의 텍스처입니다.
	/// </summary>
	std::shared_ptr<IAstrumTexture> texture;
	/// <summary>
	/// 텍스처의 크기에 따라 재질의 크기를 설정합니다.
	/// </summary>
	void SetupTextureSize();

public:
	/// <summary>
	/// AstrumMaterial 객체의 공유 포인터를 생성합니다. (이미지 파일 경로로부터)
	/// </summary>
	/// <param name="path">로드할 이미지 파일의 경로입니다.</param>
	/// <returns>새로 생성된 AstrumMaterial 공유 포인터입니다.</returns>
	static std::shared_ptr<class AstrumMaterial> MakeShared(const std::wstring& path) { return std::make_shared<AstrumMaterial>(path); }
	/// <summary>
	/// AstrumMaterial 객체의 공유 포인터를 생성합니다. (텍스처 객체로부터)
	/// </summary>
	/// <param name="texture">설정할 텍스처입니다.</param>
	/// <returns>새로 생성된 AstrumMaterial 공유 포인터입니다.</returns>
	static std::shared_ptr<class AstrumMaterial> MakeShared(const std::shared_ptr<IAstrumTexture>& texture) { return std::make_shared<AstrumMaterial>(texture); }
	/// <summary>
	/// AstrumMaterial 객체의 공유 포인터를 생성합니다. (텍스처 객체로부터, 우측값 참조 버전)
	/// </summary>
	/// <param name="texture">설정할 텍스처입니다.</param>
	/// <returns>새로 생성된 AstrumMaterial 공유 포인터입니다.</returns>
	static std::shared_ptr<class AstrumMaterial> MakeShared(std::shared_ptr<IAstrumTexture>&& texture) { return std::make_shared<AstrumMaterial>(std::move(texture)); }
};
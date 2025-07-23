#pragma once
#include "AstrumTexture.hpp"
#include "AstrumMaterialConstantBuffer.hpp"
#include "AstrumTextureSampler.hpp"
#include "IAstrumShaders.hpp"

// 텍스쳐 + 픽셀 셰이더 + 정점
class AstrumMaterial : public AstrumMaterialConstantBuffer
{
public:
	// 해당 경로로 즉시 텍스쳐를 가져오며, 그 사이 공유 포인터는 자동으로 생성합니다.
	AstrumMaterial(const wstring& path);
	AstrumMaterial(const std::shared_ptr<AstrumTexture>& texture);
	virtual ~AstrumMaterial();

	std::shared_ptr<IAstrumShaderPipeline> CustomShaderPipeline = nullptr;
	AstrumTexture& GetTexture() const;
private:
	std::shared_ptr<AstrumTexture> texture;
};
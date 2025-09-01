#pragma once
#include <string>
#include <memory>
#include "../Buffers/AstrumMaterialConstantBuffer.hpp"
#include "../Graphics/AstrumTextureSampler.hpp"
#include "../Shaders/IAstrumShaders.hpp"
#include "IAstrumMaterial.hpp"
#include "IAstrumTexture.hpp"

class IAstrumMaterial;

// 텍스쳐 + 픽셀 셰이더 + 정점
class AstrumMaterial : public AstrumMaterialConstantBuffer, public IAstrumMaterial
{
public:
	// 해당 경로의 이미지 파일로 즉시 텍스쳐를 가져오며, 그 사이 공유 포인터는 자동으로 생성합니다.
	AstrumMaterial(const std::wstring& path);
	AstrumMaterial(const std::shared_ptr<IAstrumTexture>& texture);
	AstrumMaterial(std::shared_ptr<IAstrumTexture>&& texture);

	std::shared_ptr<struct IAstrumShaderSetup> CustomShaderPipeline = nullptr;
	virtual std::shared_ptr<IAstrumTexture> GetTexture() const override { return texture; }
	virtual void SetTexture(const std::shared_ptr<IAstrumTexture>& newTexture) override;
	void SetTexture(std::shared_ptr<IAstrumTexture>&& newTexture);

private:
	virtual std::shared_ptr<struct IAstrumShaderSetup> GetCustomShaderPipeline() const override { return CustomShaderPipeline; }
	std::shared_ptr<IAstrumTexture> texture;
	void SetupTextureSize();

public:
	static std::shared_ptr<class AstrumMaterial> MakeShared(const std::wstring& path) { return std::make_shared<AstrumMaterial>(path); }
	static std::shared_ptr<class AstrumMaterial> MakeShared(const std::shared_ptr<IAstrumTexture>& texture) { return std::make_shared<AstrumMaterial>(texture); }
	static std::shared_ptr<class AstrumMaterial> MakeShared(std::shared_ptr<IAstrumTexture>&& texture) { return std::make_shared<AstrumMaterial>(std::move(texture)); }
};
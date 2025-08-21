#pragma once
#include <string>
#include <memory>
#include "../Buffers/AstrumMaterialConstantBuffer.hpp"
#include "../Graphics/AstrumTextureSampler.hpp"
#include "../Shaders/IAstrumShaders.hpp"
#include "IAstrumMaterial.hpp"
#include "AstrumTexture.hpp"

class AstrumTexture;
class IAstrumMaterial;

// 텍스쳐 + 픽셀 셰이더 + 정점
class AstrumMaterial : public AstrumMaterialConstantBuffer, public IAstrumMaterial
{
public:
	virtual ~AstrumMaterial() override;

	// 해당 경로로 즉시 텍스쳐를 가져오며, 그 사이 공유 포인터는 자동으로 생성합니다.
	AstrumMaterial(const std::wstring& path);
	AstrumMaterial(const std::shared_ptr<class AstrumTexture>& texture);

	std::shared_ptr<struct IAstrumShaderSetup> CustomShaderPipeline = nullptr;
	virtual std::shared_ptr<AstrumTexture> GetTexture() const override;
private:
	virtual std::shared_ptr<struct IAstrumShaderSetup> GetCustomShaderPipeline() const override;
	std::shared_ptr<AstrumTexture> texture;

public:
	static std::shared_ptr<class AstrumMaterial> MakeShared(const std::shared_ptr<AstrumTexture>& texture) { return std::make_shared<AstrumMaterial>(texture); }
	static std::shared_ptr<class AstrumMaterial> MakeShared(const std::wstring& path) { return std::make_shared<AstrumMaterial>(path); }
};
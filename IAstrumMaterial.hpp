#pragma once
#include <memory>
#include "AstrumTexture.hpp"
#include "AstrumTextureMesh.hpp"
#include "AstrumTextureVertex.hpp"

class IAstrumMaterial
{
	using uint = unsigned int;

public:
	virtual std::shared_ptr<IAstrumShaderSetup> GetCustomShaderPipeline() const = 0;
	virtual std::shared_ptr<AstrumTexture> GetTexture() const = 0;

	unsigned int GetTextureWidth() const;
	unsigned int GetTextureHeight() const;

	// 텍스쳐 원본 크기에 맞는 매시를 생성합니다.
	std::shared_ptr<AstrumTextureMesh> CreateTextureSizeMesh(float z = 0) const;
	// 텍스쳐에서 일부분만 가져오는 매시를 생성합니다.
	std::shared_ptr<AstrumTextureMesh> CreateCustomSizeMesh(uint left, uint top, uint width, uint height, float z = 0) const;
};
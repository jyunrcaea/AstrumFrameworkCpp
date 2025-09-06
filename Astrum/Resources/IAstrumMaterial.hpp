#pragma once
#include <memory>
#include "IAstrumTexture.hpp"
#include "../Meshes/AstrumTextureMesh.hpp"
#include "../Shaders/IAstrumShaders.hpp"

class AstrumTextureMesh;

class IAstrumMaterial
{
	using uint = unsigned int;

public:
	virtual ~IAstrumMaterial() = default;

	virtual std::shared_ptr<IAstrumShaderSetup> GetCustomShaderPipeline() const = 0;
	virtual std::shared_ptr<IAstrumTexture> GetTexture() const = 0;

	// 텍스쳐를 설정합니다.
	virtual void SetTexture(const std::shared_ptr<IAstrumTexture>& newTexture) = 0;

	unsigned int GetTextureWidth() const;
	unsigned int GetTextureHeight() const;

	// 텍스쳐 원본 크기에 맞는 매시를 생성합니다.
	std::shared_ptr<AstrumTextureMesh> CreateTextureSizeMesh(float z = 0) const;
	// 텍스쳐에서 일부분만 가져오는 매시를 생성합니다.
	std::shared_ptr<AstrumTextureMesh> CreateCustomSizeMesh(uint left, uint top, uint width, uint height, float z = 0) const;
	// 텍스쳐에서 비율을 입력받아 일부분만 가져오는 매시를 생성합니다. (텍스쳐 좌표 기준은 왼쪽 위가 (0.0, 0.0), 오른쪽 아래가 (1.0, 1.0) 입니다.)
	std::shared_ptr<AstrumTextureMesh> CreateCustomSizeMeshFromRatio(float left, float top, float right, float bottom, float z = 0) const;
};
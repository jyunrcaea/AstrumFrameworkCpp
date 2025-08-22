#pragma once
#include <string>
#include <memory>
#include "../Buffers/AstrumMaterialConstantBuffer.hpp"
#include "../Graphics/AstrumTextureSampler.hpp"
#include "../Shaders/IAstrumShaders.hpp"
#include "IAstrumMaterial.hpp"
#include "IAstrumTexture.hpp"

namespace Astrum
{
	class IMaterial;
	class ITexture;
	struct IShaderSetup;

	// 텍스쳐 + 픽셀 셰이더 + 정점
	class Material : public MaterialConstantBuffer, public IMaterial
	{
	public:
		// 해당 경로의 이미지 파일로 즉시 텍스쳐를 가져오며, 그 사이 공유 포인터는 자동으로 생성합니다.
		Material(const std::wstring& path);
		Material(const std::shared_ptr<ITexture>& texture);
		Material(std::shared_ptr<ITexture>&& texture);

		std::shared_ptr<struct IShaderSetup> CustomShaderPipeline = nullptr;
		virtual std::shared_ptr<ITexture> GetTexture() const override { return texture; }
		virtual void SetTexture(const std::shared_ptr<ITexture>& newTexture) override;
		void SetTexture(std::shared_ptr<ITexture>&& newTexture);

	private:
		virtual std::shared_ptr<struct IShaderSetup> GetCustomShaderPipeline() const override { return CustomShaderPipeline; }
		std::shared_ptr<ITexture> texture;
		void SetupTextureSize();

	public:
		static std::shared_ptr<class Material> MakeShared(const std::shared_ptr<ITexture>& texture) { return std::make_shared<Material>(texture); }
		static std::shared_ptr<class Material> MakeShared(const std::wstring& path) { return std::make_shared<Material>(path); }
	};
}
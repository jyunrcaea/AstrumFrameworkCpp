#pragma once
#include "AstrumComponent.hpp"
#include "../Buffers/AstrumTransformConstantBuffer.hpp"
#include "../Graphics/IAstrumRenderable.hpp"

namespace Astrum {
	struct IShaderSetup;

	// 렌더링을 수행하는 기본 컴포넌트입니다.
	class RenderComponent : public Component, public IRenderable {
	public:
		virtual std::shared_ptr<IShaderSetup> GetDefaultShaderPipeline() const = 0;
		std::shared_ptr<IShaderSetup>& GetCustomShaderPipeline() { return CustomShaderPipeline; }
		void SetCustomShaderPipeline(const std::shared_ptr<IShaderSetup>& shader) { CustomShaderPipeline = shader; }
		void SetCustomShaderPipeline(std::shared_ptr<IShaderSetup>&& shader) { CustomShaderPipeline = std::move(shader); }

		virtual void Draw() override;
	protected:
		std::shared_ptr<IShaderSetup> CustomShaderPipeline = nullptr;
		// 셰이더를 설정합니다.
		virtual void Render() override;
		// 렌더링전 컴포넌트 소유자(IObject)의 transform를 가져와 상수 버퍼에 넣게 될 행렬을 계산합니다.
		virtual void PreRender() override;

	private:
		TransformConstantBuffer transformBuffer;
	};
}
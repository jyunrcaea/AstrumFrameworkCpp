#pragma once
#include	<memory>
#include "AstrumComponent.hpp"
#include "../Buffers/IAstrumConstantBuffer.hpp"

namespace Astrum {
	class ConstantBufferComponent : public Component
	{
	public:
		ConstantBufferComponent();
		ConstantBufferComponent(const std::shared_ptr<IConstantBuffer>& buffer);
		ConstantBufferComponent(std::shared_ptr<IConstantBuffer>&& buffer);

		virtual void Draw() override;

	public:
		std::shared_ptr<IConstantBuffer> ConstantBuffer = nullptr;

	public:
		static std::shared_ptr<ConstantBufferComponent> MakeShared() {
			return std::make_shared<ConstantBufferComponent>();
		}
		static std::shared_ptr<ConstantBufferComponent> MakeShared(const std::shared_ptr<IConstantBuffer>& buffer) {
			return std::make_shared<ConstantBufferComponent>(buffer);
		}
		static std::shared_ptr<ConstantBufferComponent> MakeShared(std::shared_ptr<IConstantBuffer>&& buffer) {
			return std::make_shared<ConstantBufferComponent>(std::move(buffer));
		}
	};
}
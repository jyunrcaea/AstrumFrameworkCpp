#include "AstrumConstantBufferComponent.hpp"

namespace Astrum {
	ConstantBufferComponent::ConstantBufferComponent() {}
	ConstantBufferComponent::ConstantBufferComponent(const std::shared_ptr<IConstantBuffer>& buffer)
		: ConstantBuffer(buffer) { }
	ConstantBufferComponent::ConstantBufferComponent(std::shared_ptr<IConstantBuffer>&& buffer)
		: ConstantBuffer(std::move(buffer)) {}

	void ConstantBufferComponent::Draw() {
		if (ConstantBuffer) ConstantBuffer->UpdateBuffer();
	}
}

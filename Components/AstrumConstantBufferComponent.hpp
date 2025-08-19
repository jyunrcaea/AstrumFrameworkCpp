#pragma once
#include	<memory>
#include "AstrumComponent.hpp"
#include "../Buffers/IAstrumConstantBuffer.hpp"

class AstrumConstantBufferComponent : public AstrumComponent
{
public:
	AstrumConstantBufferComponent();
	AstrumConstantBufferComponent(const std::shared_ptr<IAstrumConstantBuffer>& buffer);
	AstrumConstantBufferComponent(std::shared_ptr<IAstrumConstantBuffer>&& buffer);

	virtual void Draw() override;

public:
	std::shared_ptr<IAstrumConstantBuffer> ConstantBuffer = nullptr;

public:
	static std::shared_ptr<AstrumConstantBufferComponent> MakeShared() {
		return std::make_shared<AstrumConstantBufferComponent>();
	}
	static std::shared_ptr<AstrumConstantBufferComponent> MakeShared(const std::shared_ptr<IAstrumConstantBuffer>& buffer) {
		return std::make_shared<AstrumConstantBufferComponent>(buffer);
	}
	static std::shared_ptr<AstrumConstantBufferComponent> MakeShared(std::shared_ptr<IAstrumConstantBuffer>&& buffer) {
		return std::make_shared<AstrumConstantBufferComponent>(std::move(buffer));
	}
};
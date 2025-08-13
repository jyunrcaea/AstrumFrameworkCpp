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
};
#pragma once
#include	<memory>
#include "AstrumComponent.hpp"
#include "../Buffers/IAstrumConstantBuffer.hpp"

class AstrumConstantBufferComponent : public AstrumComponent
{
public:
	AstrumConstantBufferComponent(const std::shared_ptr<IAstrumConstantBuffer>& constantBuffer = nullptr);
	virtual void PreRender() override;
	std::shared_ptr<IAstrumConstantBuffer> ConstantBuffer;
};
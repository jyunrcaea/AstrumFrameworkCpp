#pragma once
#include <memory>
#include "AstrumRenderMaterialComponent.hpp"
#include "../Buffers/IAstrumConstantBuffer.hpp"
#include "../Objects/AstrumObject.hpp"

class AstrumPostProcessRenderComponent : public AstrumRenderMaterialComponent
{
public:
	AstrumPostProcessRenderComponent(const std::shared_ptr<IAstrumConstantBuffer>& constantBuffer = nullptr);
	AstrumPostProcessRenderComponent(std::shared_ptr<IAstrumConstantBuffer>&& constantBuffer);

	virtual IAstrumObject* GetOwner() const override;

	std::shared_ptr<IAstrumConstantBuffer> ConstantBuffer = nullptr;

protected:
	virtual void Render() override;

public:
	static std::shared_ptr<AstrumPostProcessRenderComponent> MakeShared(const std::shared_ptr<IAstrumConstantBuffer>& constantBuffer = nullptr) {
		return std::make_shared<AstrumPostProcessRenderComponent>(constantBuffer);
	}
	static std::shared_ptr<AstrumPostProcessRenderComponent> MakeShared(std::shared_ptr<IAstrumConstantBuffer>&& constantBuffer) {
		return std::make_shared<AstrumPostProcessRenderComponent>(std::move(constantBuffer));
	}
};
#pragma once
#include "IAstrumComponent.hpp"

class AstrumComponent : public IAstrumComponent
{
public:
	virtual ~AstrumComponent() = default;
	virtual void Prepare() override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void PreRender() override;

	virtual void SetOwner(IAstrumObject* owner);
	virtual IAstrumObject* GetOwner() const;

private:
	IAstrumObject* owner = nullptr;
};